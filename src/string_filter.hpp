#ifndef STRING_FILTER
#define STRING_FILTER

#include <unordered_set>

namespace text_filter {
    using namespace std;

    class string_filter {
    public:
        void add_word(string word);
        bool search_word(string word);
        string filter(string input);
        template<typename FilterAlgorithm>
        string filter(string input, FilterAlgorithm algo);
        unordered_set<string> list_all_blocked_words();
    private:
        unordered_set<string> blocked_words;
    };

    namespace algorithm {
        class brute_force {
        public:
            string operator()(string input)
            {
                //TODO
                return input;
            }
        };

        //TODO
    }
}

#endif /* STRING_FILTER */