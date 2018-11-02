#ifndef TEST_FILTER
#define TEST_FILTER

#include <fstream>
#include <string>
#include "algorithm/algo_base.hpp"

namespace text_filter {
    class string_filter;

    class test_filter {
    public:
        void run();
    private:
        void open_resource_file(std::wstring, std::string);
        void test_algorithm(algorithm::algo_base&, unsigned times = 1);

        string_filter filter;
        std::wifstream fs;
    };
}

#endif /* TEST_FILTER */