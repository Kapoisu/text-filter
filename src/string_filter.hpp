#ifndef STRING_FILTER
#define STRING_FILTER

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace text_filter {
    class string_filter {
    public:
        void add_word(std::string word);
        void reset();
        std::unordered_set<std::string> list_all_blocked_words() const;
        std::string filter(std::string input);
        template<typename FilterAlgorithm>
        std::string filter(std::string input, FilterAlgorithm algo)
        {
            return algo(input, blocked_words);
        }
    private:
        std::unordered_set<std::string> blocked_words;
    };

    namespace algorithm {
        class brute_force {
        public:
            std::string operator()(std::string input, std::unordered_set<std::string> blocked_words);
        private:
            std::string operator()(std::string input, std::string word);
        };

        class knuth_morris_pratt {
        public:
            std::string operator()(std::string input, std::unordered_set<std::string> blocked_words);
        private:
            std::string operator()(std::string input, std::string word);
            void generate_table(std::string key);
            std::unordered_map<std::string, std::vector<int>> offset_if_fail;
        };

        class aho_corasick {
        public:
            std::string operator()(std::string input, std::unordered_set<std::string> blocked_words);
        private:
            struct node {
            public:
                node() : inDict(false), suffix(nullptr)/*, dict_suffix(nullptr)*/ {}
                void add_word(std::string);
                void add_suffix(node* root);
                std::unordered_map<char, std::shared_ptr<node>> child;
                bool inDict;
                node* suffix;
                //node* dict_suffix;
            };

            node root;
            void build_trie(std::unordered_set<std::string> blocked_words);
            void build_suffix();
        };

        //TODO
    }
}

#endif /* STRING_FILTER */