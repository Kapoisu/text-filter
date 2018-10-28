#ifndef STRING_FILTER
#define STRING_FILTER

#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace text_filter {
    class string_filter {
    public:
        void add_word(std::string word);
        bool search_word(std::string word) const;
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
        };


        //TODO
    }
}

#endif /* STRING_FILTER */