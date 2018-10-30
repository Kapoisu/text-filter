#include <iostream>
#include <string>
#include <unordered_set>
#include "string_filter.hpp"

int main()
{
    using namespace std;
    using namespace text_filter;

    string_filter filter;
    auto quit = false;
    string input;

    do {
        cout << "Enter the operation:" << endl;
        cout << "a: add word." << endl;
        cout << "f: filter the input." << endl;
        cout << "q: quit." << endl;
        cout << endl;

        switch(cin.get()) {
        case 'a':
            cout << "add: ";
            cin >> input;
            filter.add_word(input);
            break;
        case 'f':
            cout << "input: ";
            cin >> input;
            cout << filter.filter(input) << endl;
            break;
        case 'q':
            quit = true;
            break;
        default:
            break;
        }

        cin.ignore();
        cout << endl;
    } while(!quit);
}