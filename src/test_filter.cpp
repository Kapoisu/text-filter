#include <iostream>
#include <chrono>
#include <fstream>
#include "test_filter.hpp"

namespace text_filter {
    void test_filter::run()
    {
        using std::wcin;
        using std::wcout;
        using std::wifstream;
        using std::wstring;
        using std::endl;
        using namespace std::chrono;
		using namespace algorithm;

        aho_corasick func;
        unsigned num;
        wifstream dict("pattern.txt");

        wcout << L"starting to run test...\n" << endl;
        wcout << L"enter the number of test case: ";
        wcin >> num;

        wcin.tie(0);

        if(!dict.is_open()) {
            wcout << L"file not found." << endl;
            return;
        }

        wstring buffer;
        while(dict >> buffer) {
            wcout << L"add word: ";
            wcout << buffer << endl;
            filter.add_word(buffer);
        }

        dict.close();

        wcout << endl << "generating test cases..." << endl;

        wifstream test_brute_force("testdata.txt");

        auto start = high_resolution_clock::now();

        /*for(auto i = 0; i < num; ++i) {
            if(!getline(test_brute_force, buffer)) {
                break;
            }
			if (i % 10000 == 0) {
				wcout << L"\nprocessing the " << i << "th test case..." << endl;
			}

            filter.filter(buffer, brute_force());
        }*/

		auto end = high_resolution_clock::now();

		/* wcout << L"\nusing brute-force algorithm..." << endl;
		wcout << L"test case amount: " << num << endl;
		wcout << L"computing time: " << duration_cast<seconds>(end - start).count() << "s" << endl;

		wifstream test_kmp("testdata.txt"); */

		start = high_resolution_clock::now();

		/* for (auto i = 0; i < num; ++i) {
			if (!getline(test_kmp, buffer)) {
				break;
			}
			if (i % 10000 == 0) {
				wcout << L"\nprocessing the " << i << "th test case..." << endl;
			}

			filter.filter(buffer, knuth_morris_pratt());
		} */

		end = high_resolution_clock::now();

		/* wcout << L"\nusing Knuth-Morris-Pratt algorithm..." << endl;
		wcout << L"test case amount: " << num << endl;
		wcout << L"computing time: " << duration_cast<seconds>(end - start).count() << "s" << endl; */

		wifstream test_aho_corasick("testdata.txt");

		start = high_resolution_clock::now();

		for (auto i = 0; i < num; ++i) {
			if (!getline(test_aho_corasick, buffer)) {
				break;
			}
			if (i + 1 % 10000 == 0) {
				wcout << L"\nprocessing the " << i + 1 << "th test case..." << endl;
			}

			filter.filter(buffer, std::ref(func));
		}

		end = high_resolution_clock::now();

		wcout << L"\nusing Aho-Corasick algorithm..." << endl;
		wcout << L"test case amount: " << num << endl;
		wcout << L"computing time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;

        wcout << "\ntest finish." << endl;
    }
}