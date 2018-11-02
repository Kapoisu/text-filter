#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include "string_filter.hpp"
#include "test_filter.hpp"

int main()
{
    using namespace text_filter;
    using namespace std;

    ios_base::sync_with_stdio(false);
    setlocale(LC_ALL, "");

    string_filter filter;
    wstring command;
    wstring operation;
    wstring argument;

    wcout << L"Enter \"help\" to see the manual.\n" << endl;
    while(true) {
        wcout << L"$ text-filter ";
        wcout.flush();
        getline(wcin, command);
        wstringstream input(command);
        input >> operation;

        if(operation == L"add") {
            while(input >> argument) {
                wcout << L"add word: " << argument << endl;
                filter.add_word(argument);
            }
        }
        else if(operation == L"filter") {
            getline(input, argument);
            wcout << L"input: " << argument << endl;
            wcout << L"output: " << filter.filter(argument) << endl;
        }
        else if(operation == L"reset") {
            wcout << L"reset filter." << endl;
            filter.reset();
        }
        else if(operation == L"quit") {
            break;
        }
        else if(operation == L"test") {
            test_filter test;
            test.run();
        }
        else if(operation == L"help") {
            wcout << L"add: add a word you want to block." << endl;
            wcout << L"filter: generate the filtered output." << endl;
            wcout << L"reset: clear already added words." << endl;
            wcout << L"test: enter test mode." << endl;
            wcout << L"quit: exit the program." << endl;
        }
        else {
            wcout << operation << L": command not found." << endl;
        }

        wcout << endl;

        operation.clear();
    };
}