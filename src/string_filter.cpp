#include <algorithm>
#include <vector>
#include <queue>
#include "string_filter.hpp"

namespace text_filter {
    using namespace std;
    using namespace algorithm;

    void string_filter::add_word(string word)
    {
        blocked_words.insert(word);
    }

    bool string_filter::search_word(string word) const
    {
        return blocked_words.count(word);
    }

    unordered_set<string> string_filter::list_all_blocked_words() const
    {
        return blocked_words;
    }

    string string_filter::filter(string input)
    {
        return filter(move(input), knuth_morris_pratt());
    }

    namespace algorithm {
        string brute_force::operator()(string input, unordered_set<string> blocked_words)
        {
            for(auto const& word : blocked_words) {
                input = operator()(move(input), word);
            }

            return input;
        }

        string brute_force::operator()(string input, string word)
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

        string knuth_morris_pratt::operator()(string input, unordered_set<string> blocked_words)
        {
            for(auto const& word : blocked_words) {
                input = operator()(move(input), word);
            }

            return input;
        }

        string knuth_morris_pratt::operator()(string input, string word)
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

        void knuth_morris_pratt::generate_table(string key)
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

        string aho_corasick::operator()(string input, unordered_set<string> blocked_words)
        {
            build_trie(blocked_words);
            //build_suffix();
            //TODO

            return "";
        }

        void aho_corasick::build_trie(unordered_set<string> blocked_words)
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
            }
        }/*

        void aho_corasick::build_suffix()
        {
            node *p;
            queue<node*> q;
            this->root.suffix = &(this->root);
            q.push(&(this->root));

            while(q.size() > 0) {
                p = q.front();
                for(auto const& n : p->child) {
                    while(p->suffix->child.count(n.first) == 0) {
                        p = p->suffix;
                    }

                    if(p == &(this->root)) {
                        n.second->suffix = p;
                    }
                    else {
                        n.second->suffix = p->suffix->child[n.first].get();
                    }

                    q.push(n.second.get());
                }
                q.pop();
            }
        }*/

        void aho_corasick::node::add_word(string word)
        {
            node &p = *this;

            for(auto const& c : word) {
                if(child.count(c) == 0) {
                    p.child[c] = make_shared<node>();
                }

                p = *p.child[c];
            }
        }

        void aho_corasick::node::add_suffix(node* root)
        {
            if(this == root) {
                this->suffix = root;
                this->dict_suffix = root;
            }
        }
    }
}