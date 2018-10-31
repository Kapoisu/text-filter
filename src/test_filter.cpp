#include <iostream>
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

        unsigned num;
        std::wifstream dict("pattern.txt");

        wcout << "starting to run test...\n" << endl;
        wcout << "enter the number of test case: ";
        wcin >> num;

        if(!dict.is_open()) {
            wcout << "file not found." << endl;
            return;
        }

        wstring word;
        while(dict >> word) {
            wcout << "add word: ";
            wcout << word << endl;
            filter.add_word(word);
        }

        wcout << endl << "generating test cases...\n" << endl;

        wcout << "test finish." << endl;
    }
}