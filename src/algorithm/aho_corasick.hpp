#ifndef AHO_CORASICK
#define AHO_CORASICK

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace text_filter {
    namespace algorithm {
        class aho_corasick {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
        private:
            struct node {
            public:
                node() : inDict(false), suffix(nullptr), dict_suffix(nullptr) {}
                void add_word(std::wstring);
                void add_suffix(node* root);
                std::unordered_map<char, std::shared_ptr<node>> child;
                bool inDict;
                node* suffix;
                node* dict_suffix;
            };

            node root;
            void build_trie(std::unordered_set<std::wstring> blocked_words);
        };
    }
}

#endif /* AHO_CORASICK */