#ifndef ALGO_BASE
#define ALGO_BASE

#include <string>
#include <unordered_set>

namespace text_filter {
    namespace algorithm {
        class algo_base {
        public:
            virtual std::wstring operator()(std::wstring input, std::unordered_set<std::wstring>) = 0;
            virtual std::wstring get_name() = 0;
        };
    }
}

#endif /* ALGO_BASE */