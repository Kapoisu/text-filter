#include <algorithm>
#include "string_filter.hpp"

namespace text_filter {
    void string_filter::add_word(string word)
    {
        blocked_words.insert(word);
    }

    bool string_filter::search_word(string word)
    {
        return blocked_words.count(word);
    }

    string string_filter::filter(string input)
    {
        return filter(input, algorithm::brute_force());
    }

    template<typename FilterAlgorithm>
    string string_filter::filter(string input, FilterAlgorithm algo)
    {
        return algo(input);
    }

    unordered_set<string> string_filter::list_all_blocked_words()
    {
        return blocked_words;
    }
}