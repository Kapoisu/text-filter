#include <iostream>
#include <fstream>
#include "test_filter.hpp"

namespace text_filter {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::wstring;
    using std::wifstream;

    void test_filter::run()
    {
        unsigned num;
        wifstream dict;

        cout << "starting to run test...\n" << endl;
        cout << "enter the number of test case: ";
        cin >> num;
        do {
            string filepath;
            cout << "enter the dictionary filepath: ";
            cin >> filepath;
            dict.open(filepath);
        } while(!dict.good());

        wstring word;
        while(dict >> word) {
            filter.add_word(word);
        }

        cout << "test finish." << endl;
    }
}