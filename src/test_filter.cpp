#include <chrono>
#include <iostream>
#include "test_filter.hpp"
#include "algorithm/algo_base.hpp"

namespace text_filter {
    using namespace std;
    using namespace algorithm;

    void test_filter::run()
    {
        brute_force func_brute_force;
        knuth_morris_pratt func_kmp;
        aho_corasick func_aho_corasick;

        unsigned num;

        wcout << L"Starting to run test...\n\n";

        wcout << L"Enter the number of test case: ";
        wcin >> num;
        wcin.ignore();

        wifstream fs = open_resource_file<resource_type::pattern>(L"Enter the name of file that contains the string patterns you want to filter (default: pattern.txt): ");

        wcout << L"Loading the patterns...\n" << endl;
        wstring buffer;
        while(fs >> buffer) {
            filter.add_word(move(buffer));
        }

        //test_algorithm(func_brute_force, num);
        //test_algorithm(func_kmp, num);
        test_algorithm(func_aho_corasick, num);

        wcout << "Test finish." << endl;
    }

    template<test_filter::resource_type R>
    wifstream test_filter::open_resource_file(wstring message)
    {
        wifstream fs;
        do {
            wstring filename;
            wcout << message;
            getline(wcin, filename);
            //issue: cannot pass wstring
            fs.open(get_default_filename<R>());

            if(!fs.is_open()) {
                wcout << L": file not found.\n";
                wcout << L"Enter the filename again: ";
                filename.clear();
            }
        } while(!fs.is_open());

        return fs;
    }

    void test_filter::test_algorithm(algo_base& algo, unsigned times)
    {
        using namespace chrono;

        wstring buffer;
        wifstream fs = open_resource_file<resource_type::testdata>(L"Enter the name of file that contains the test cases (default: testdata.txt): ");

        wcout << L"\nUsing "<< algo.get_name() << L" algorithm...\n" << endl;

        auto start = high_resolution_clock::now();

        for(auto i = 1; i <= times; ++i) {
            if(!getline(fs, buffer)) {
                break;
            }

            filter.filter(move(buffer), ref(algo));
        }

        auto end = high_resolution_clock::now();

        wcout << L"Test case amount: " << times;
        wcout << L"\nComputing time: " << duration_cast<milliseconds>(end - start).count() << "ms\n" << endl;
    }
}