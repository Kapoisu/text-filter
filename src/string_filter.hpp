#ifndef STRING_FILTER
#define STRING_FILTER

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "algorithm/aho_corasick.hpp"
#include "algorithm/brute_force.hpp"
#include "algorithm/knuth_morris_pratt.hpp"

namespace text_filter {
    class string_filter {
    public:
        void add_word(std::wstring word);
        void reset();
        std::wstring filter(std::wstring input);
        template<typename FilterAlgorithm>
        std::wstring filter(std::wstring input, FilterAlgorithm algo)
        {
            return algo(input, blocked_words);
        }
    private:
        std::unordered_set<std::wstring> blocked_words;
    };
}

#endif /* STRING_FILTER */