#ifndef TEST_FILTER
#define TEST_FILTER

#include "string_filter.hpp"

namespace text_filter {
    class test_filter {
    public:
        void run();
    private:
        string_filter filter;
    };
}

#endif /* TEST_FILTER */