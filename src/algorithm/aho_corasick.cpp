#include <queue>
#include "aho_corasick.hpp"

namespace text_filter {
    namespace algorithm {
        using namespace std;

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