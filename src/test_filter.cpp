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
        using std::chrono::high_resolution_clock;
        using std::chrono::seconds;
        using std::chrono::duration_cast;
        using algorithm::knuth_morris_pratt;

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
        int count = 0;
        while(dict >> buffer) {
            wcout << L"add word: ";
            wcout << buffer << endl;
            filter.add_word(buffer);
            count++;
        }

        dict.close();

        wcout << endl << "generating test cases..." << endl;

        wifstream testcase("testdata.txt");

        auto start = high_resolution_clock::now();

        while(getline(testcase, buffer)) {
            wcout << L"\ninput: " << buffer << L"\n";
            wcout << L"\noutput: " << filter.filter(buffer) << L"\n";
            wcout << L"\noutput: " << filter.filter(buffer, knuth_morris_pratt()) << L"\n";
        }

        auto end = high_resolution_clock::now();

        wcout << endl << L"computing time: " << duration_cast<seconds>(end - start).count() << "s" << endl;

        wcout << endl << "test finish." << endl;
    }
}