#ifndef BRUTE_FORCE
#define BRUTE_FORCE

#include "algo_base.hpp"

namespace text_filter {
    namespace algorithm {
        class brute_force : public algo_base {
        public:
            std::wstring get_name() { return L"brute-force"; }
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring>& blocked_words);
            std::wstring operator()(std::wstring input, std::wstring word);
        };
    }
}

#endif /* BRUTE_FORCE */