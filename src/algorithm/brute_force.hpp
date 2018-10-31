#ifndef BRUTE_FORCE
#define BRUTE_FORCE

#include <string>
#include <unordered_set>

namespace text_filter {
    namespace algorithm {
        class brute_force {
        public:
            std::wstring operator()(std::wstring input, std::unordered_set<std::wstring> blocked_words);
        private:
            std::wstring operator()(std::wstring input, std::wstring word);
        };
    }
}

#endif /* BRUTE_FORCE */