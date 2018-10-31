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
        return filter(move(input), aho_corasick());
    }
}