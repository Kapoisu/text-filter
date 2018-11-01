#include <sstream>
#include <vector>
#include "knuth_morris_pratt.hpp"

namespace text_filter {
    namespace algorithm {
        using namespace std;

        wstring knuth_morris_pratt::operator()(wstring input, unordered_set<wstring> blocked_words)
        {
            for(auto const& word : blocked_words) {
                generate_table(word);
            }

            for(auto const& pair : offset_if_fail) {
                input = operator()(move(input), pair.first);
            }

            return input;
        }

        wstring knuth_morris_pratt::operator()(wstring input, wstring word)
        {
            auto inputPos = 0, wordPos = 0, start = 0;
            while(inputPos < input.size()) {
                if(word[wordPos] == input[inputPos]) {
                    ++wordPos;
                    ++inputPos;

                    if(wordPos == word.size()) {
                        auto replacePos = inputPos - wordPos;
                        input.replace(input.cbegin() + replacePos, input.cbegin() + replacePos + word.size(), word.size(), '*');

                        wordPos = offset_if_fail[word][wordPos];
                    }
                }
                else {
                    wordPos = offset_if_fail[word][wordPos];
                    if(wordPos < 0) {
                        ++wordPos;
                        ++inputPos;
                    }
                }
            }

            return input;
        }

        void knuth_morris_pratt::generate_table(wstring key)
        {
            if(offset_if_fail.count(key) > 0) {
                return;
            }

            vector<int> table(key.size() + 1);

            table[0] = -1;
            auto pos = 1, cnd = 0;

            while(pos < key.size()) {
                if(key[pos] == key[cnd]) {
                    table[pos] = table[cnd];
                }
                else {
                    table[pos] = cnd;
                    cnd = table[cnd];

                    while(cnd >= 0 && key[pos] != key[cnd]) {
                        cnd = table[cnd];
                    }
                }

                ++pos;
                ++cnd;
            }

            table[pos] = cnd;
            offset_if_fail[key] = table;
        }
    }
}