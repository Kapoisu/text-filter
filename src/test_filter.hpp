#ifndef TEST_FILTER
#define TEST_FILTER

#include <fstream>
#include <string>
#include "string_filter.hpp"

namespace text_filter {
    class test_filter {
    public:
        void run();
    private:
        string_filter filter;

        enum class resource_type {
            pattern,
            testdata
        };

        void test_algorithm(algorithm::algo_base&, unsigned times = 1);

        template<resource_type R>
        std::wifstream open_resource_file(std::wstring message);

        template<resource_type R>
        std::string get_default_filename()
        {
            return get_default_filename<R>();
        }
    };

    template<>
    inline std::string test_filter::get_default_filename<test_filter::resource_type::pattern>()
    {
        return "pattern.txt";
    }

    template<>
    inline std::string test_filter::get_default_filename<test_filter::resource_type::testdata>()
    {
        return "testdata.txt";
    }
}

#endif /* TEST_FILTER */