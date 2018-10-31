#ifndef STRING_FILTER
#define STRING_FILTER

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace text_filter {
    class string_filter {
    public:
        void add_word(std::wstring word);
        void reset();
        std::unordered_set<std::wstring> list_all_blocked_words() const;
        std::wstring filter(std::wstring input);
        template<typename FilterAlgorithm>
        std::wstring filter(std::wstring input, FilterAlgorithm algo)
        {
            return algo(input, blocked_words);
        }
    private:
        std::unordered_set<std::wstring> blocked_words;
    };

    namespace algorithm {
        class brute_force {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
        private:
            std::wstring operator()(std::wstring input, std::wstring word);
        };

        class knuth_morris_pratt {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
        private:
            std::wstring operator()(std::wstring input, std::wstring word);
            void generate_table(std::wstring key);
            std::unordered_map<std::wstring, std::vector<int>> offset_if_fail;
        };

        class aho_corasick {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
        private:
            struct node {
            public:
                node() : inDict(false), suffix(nullptr)/*, dict_suffix(nullptr)*/ {}
                void add_word(std::wstring);
                void add_suffix(node* root);
                std::unordered_map<char, std::shared_ptr<node>> child;
                bool inDict;
                node* suffix;
                //node* dict_suffix;
            };

            node root;
            void build_trie(std::unordered_set<std::wstring> blocked_words);
        };

        //TODO
    }
}

#endif /* STRING_FILTER */