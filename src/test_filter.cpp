#include <chrono>
#include <iostream>
#include "string_filter.hpp"
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

        wcout << L"Enter the name of file that contains the string patterns you want to filter (default: pattern.txt): ";
        open_resource_file(L"", "pattern.txt");

        wcout << L"Loading the patterns...\n" << endl;
        wstring buffer;
        while(fs >> buffer) {
            filter.add_word(buffer);
        }
        fs.close();

        wcout << L"Enter the name of file that contains the test cases (default: testdata.txt): ";
        open_resource_file(L"", "testdata.txt");

        test_algorithm(func_brute_force, num);

        test_algorithm(func_kmp, num);

        test_algorithm(func_aho_corasick, num);

        wcout << "\nTest finish." << endl;
    }

    void test_filter::open_resource_file(wstring filename, string _filename = "")
    {
        do {
            getline(wcin, filename);
            //issue: cannot pass wstring
            fs.open(_filename);

            if(!fs.is_open()) {
                wcout << L": file not found.";
                wcout << L"Enter the filename: ";
                filename.clear();
            }
        } while(!fs.is_open());
    }

    void test_filter::test_algorithm(algo_base& algo, unsigned times)
    {
        using namespace chrono;

        wstring buffer;

        wcout << L"\nUsing "<< algo.get_name() << L" algorithm...\n" << endl;

		auto start = high_resolution_clock::now();

        fs.seekg(0);
        for(auto i = 0; i < times; ++i) {
            if(!getline(fs, buffer)) {
                break;
            }

            if (i + 1 % 1000 == 0) {
				wcout << L"Processing the " << i + 1 << "th test case..." << endl;
			}

            filter.filter(buffer, std::ref(algo));
        }

		auto end = high_resolution_clock::now();

		wcout << L"Test case amount: " << times;
		wcout << L"\nComputing time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
    }
}