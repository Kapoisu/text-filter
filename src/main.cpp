#include <iostream>
#include <locale>
#include <string>
#include <unordered_set>
#include "string_filter.hpp"
#include <fstream>

int main()
{
    using namespace std;
    using namespace text_filter;

    //ios_base::sync_with_stdio(false);

    string_filter filter;
    auto quit = false;
    string input;
    fstream fs("D:/text-filter/build/src/text.txt");
    char option;
    auto g = fs.good();

    do {
        cout << "Enter the operation:" << endl;
        cout << "a: add word." << endl;
        cout << "f: filter the input." << endl;
        cout << "r: reset filter." << endl;
        cout << "q: quit." << endl;
        cout << endl;
        //cin >> option;
        option = cin.get();
        cin.ignore();


        switch(option) {
        case 'a':
            cout << "add   : ";
            cin >> input;
            filter.add_word(input);
            break;
        case 'f':
            getline(cin, input);
            cout << "input : " << input << endl;
            cout << "output: " << filter.filter(input) << endl;
            break;
        case 'r':
            filter.reset();
        case 'q':
            quit = true;
            break;
        default:
            break;
        }

        cout << endl;
    } while(!quit);
}