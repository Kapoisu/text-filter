#ifndef KNUTH_MORRIS_PRATT
#define KNUTH_MORRIS_PRATT

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace text_filter {
    namespace algorithm {
        class knuth_morris_pratt {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
        private:
            std::wstring operator()(std::wstring input, std::wstring word);
            void generate_table(std::wstring key);
            std::unordered_map<std::wstring, std::vector<int>> offset_if_fail;
        };
    }
}

#endif /* KNUTH_MORRIS_PRATT */