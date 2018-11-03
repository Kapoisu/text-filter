#ifndef KNUTH_MORRIS_PRATT
#define KNUTH_MORRIS_PRATT

#include <unordered_map>
#include "algo_base.hpp"

namespace text_filter {
    namespace algorithm {
        class knuth_morris_pratt : public algo_base {
        public:
            std::wstring get_name() { return L"Knuth-Morris-Pratt"; }
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring>& blocked_words);
            std::wstring operator()(std::wstring input, std::wstring word);
        private:
            void generate_table(std::wstring key);
            std::unordered_map<std::wstring, std::vector<int>> offset_if_fail;
        };
    }
}

#endif /* KNUTH_MORRIS_PRATT */