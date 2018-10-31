#include <iostream>
#include <locale>
#include <string>
#include <unordered_set>
#include "string_filter.hpp"
#include "test_filter.hpp"

int main()
{
    using namespace text_filter;
    using namespace std;

    ios_base::sync_with_stdio(false);
    setlocale(LC_ALL, "");

    string_filter filter;
    wstring option;
    wstring input;

    wcout << L"Enter \"help\" to see the manual.\n" << endl;
    while(true) {
        wcout << L"$ text-filter ";
        wcin >> option;

        if(option == L"add") {
            wcin >> input;
            wcout << L"add word: " << input << endl;
            filter.add_word(input);
        }
        else if(option == L"filter") {
            wcin.ignore();
            getline(wcin,input);
            wcout << L"filter input: " << input << endl;
            wcout << L"output: " << filter.filter(input) << endl;
        }
        else if(option == L"reset") {
            wcout << L"reset filter." << endl;
            filter.reset();
        }
        else if(option == L"quit") {
            break;
        }
        else if(option == L"test") {
            test_filter test;
            test.run();
        }
        else if(option == L"help") {
            wcout << L"add: add a word you want to block." << endl;
            wcout << L"filter: generate the filtered output." << endl;
            wcout << L"reset: clear already added words." << endl;
            wcout << L"test: enter test mode." << endl;
            wcout << L"quit: exit the program." << endl;
        }
        else {
            wcout << option << L": command not found." << endl;
        }

        wcout << endl;
    };
}