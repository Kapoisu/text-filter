#include <algorithm>
#include <vector>
#include <queue>
#include "string_filter.hpp"

namespace text_filter {
    using std::wstring;
    using std::unordered_set;
    using std::vector;
    using std::queue;
    using std::make_shared;
    using namespace algorithm;

    void string_filter::add_word(wstring word)
    {
        blocked_words.insert(word);
    }

    void string_filter::reset()
    {
        blocked_words.clear();
    }

    unordered_set<wstring> string_filter::list_all_blocked_words() const
    {
        return blocked_words;
    }

    wstring string_filter::filter(wstring input)
    {
        return filter(move(input), knuth_morris_pratt());
    }

    namespace algorithm {
        wstring brute_force::operator()(wstring input, unordered_set<wstring> blocked_words)
        {
            for(auto const& word : blocked_words) {
                input = operator()(move(input), word);
            }

            return input;
        }

        wstring brute_force::operator()(wstring input, wstring word)
        {
            for(auto i = 0; i < input.size() - word.size() + 1; ++i) {
                bool matched = true;
                for(auto j = 0; j < word.size(); ++j) {
                    if(input[i + j] != word[j]) {
                        matched = false;
                        break;
                    }
                }

                if(matched) {
                    input.replace(input.cbegin() + i, input.cbegin() + i + word.size(), word.size(),'*');
                }
            }

            return input;
        }

        wstring knuth_morris_pratt::operator()(wstring input, unordered_set<wstring> blocked_words)
        {
            for(auto const& word : blocked_words) {
                input = operator()(move(input), word);
            }

            return input;
        }

        wstring knuth_morris_pratt::operator()(wstring input, wstring word)
        {
            if(offset_if_fail.count(word) == 0) {
                generate_table(word);
            }

            auto inputPos = 0, wordPos = 0;

            while(inputPos < input.size()) {
                if(word[wordPos] == input[inputPos]) {
                    ++wordPos;
                    ++inputPos;
                    if(wordPos == word.size()) {
                        auto replacePos = inputPos - wordPos;
                        input.replace(input.cbegin() + replacePos, input.cbegin() + replacePos + word.size(), word.size(), '*');
                        wordPos = offset_if_fail[word][wordPos];
                    }
                }
                else {
                        wordPos = offset_if_fail[word][wordPos];
                        if(wordPos < 0) {
                            ++wordPos;
                            ++inputPos;
                        }
                    }
            }

            return input;
        }

        void knuth_morris_pratt::generate_table(wstring key)
        {
            vector<int> table(key.size() + 1);

            table[0] = -1;
            auto pos = 1, cnd = 0;

            while(pos < key.size()) {
                if(key[pos] == key[cnd]) {
                    table[pos] = table[cnd];
                }
                else {
                    table[pos] = cnd;
                    cnd = table[cnd];

                    while(cnd >= 0 && key[pos] != key[cnd]) {
                        cnd = table[cnd];
                    }
                }

                ++pos;
                ++cnd;
            }

            table[pos] = cnd;
            offset_if_fail[key] = table;
        }

        wstring aho_corasick::operator()(wstring input, unordered_set<wstring> blocked_words)
        {
            build_trie(blocked_words);

            node *p = &root;
            auto start = input.cbegin();
            auto it = input.cbegin();

            while(it != input.cend()) {
                if(p->child.count(*it) > 0) {
                    p = p->child[*it++].get();

                    if(p->inDict) {
                        input.replace(start, it, distance(start, it), '*');
                        start = it;
                        p = &root;
                    }
                }
                else {
                    p = p->suffix;
                    ++start;

                    if(p == &root) {
                        ++it;
                        start = it;
                    }
                }
            }

            return input;
        }

        void aho_corasick::build_trie(unordered_set<wstring> blocked_words)
        {
            for(auto const& word : blocked_words) {
                root.add_word(word);
            }

            queue<node*> q;
            q.push(&root);
            while(q.size() > 0) {
                node &p = *(q.front());
                p.add_suffix(&root);

                for(auto const& n : p.child) {
                    q.push(n.second.get());
                }

                q.pop();
            }
        }

        void aho_corasick::node::add_word(wstring word)
        {
            node *p = this;

            for(auto const& c : word) {
                if(p->child.count(c) == 0) {
                    p->child[c] = make_shared<node>();
                }

                p = p->child[c].get();
            }

            p->inDict = true;
        }

        void aho_corasick::node::add_suffix(node* root)
        {
            if(this == root) {
                this->suffix = root;
            }

            for(auto const& n : child) {
                node *p = this; //parent
                while(p->suffix->child.count(n.first) == 0) {
                    p = p->suffix;

                    if(p == root) {
                        n.second->suffix = p;
                        break;
                    }
                }

                if(p == root) {
                    n.second->suffix = p;
                }
                else {
                    n.second->suffix = p->suffix->child[n.first].get();
                }

                /* p = n.second->suffix;
                while(!p->inDict && p != root) {
                    p = p->suffix;
                }

                if(p != root) {
                    n.second->dict_suffix = p;
                } */
            }
        }
    }
}