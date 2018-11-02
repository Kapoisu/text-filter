#ifndef AHO_CORASICK
#define AHO_CORASICK

#include <memory>
#include <unordered_map>
#include "algo_base.hpp"

namespace text_filter {
    namespace algorithm {
        class aho_corasick : public algo_base {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
            std::wstring get_name() { return L"Aho-Corasick"; }
        private:
            struct node {
            public:
                node() : inDict(false), suffix(nullptr), dict_suffix(nullptr) {}
                void add_word(std::wstring word);
                void add_suffix(node* root);
                std::unordered_map<char, std::shared_ptr<node>> child;
                int depth;
                bool inDict;
                node* suffix;
                node* dict_suffix;
            };

            node root;
            int number_of_node;
            bool is_modified;
            void build_trie(std::unordered_set<std::wstring> blocked_words);
        };
    }
}

#endif /* AHO_CORASICK */