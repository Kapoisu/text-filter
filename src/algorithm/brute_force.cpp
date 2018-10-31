#include "brute_force.hpp"

namespace text_filter {
    namespace algorithm {
        using namespace std;

        wstring brute_force::operator()(wstring input, unordered_set<wstring> blocked_words)
        {
            for(auto const& word : blocked_words) {
                input = operator()(move(input), word);
            }

            return input;
        }

        wstring brute_force::operator()(wstring input, wstring word)
        {
            for(auto i = 0; i < input.size() - word.size() + 1; ++i) {
                bool matched = true;
                for(auto j = 0; j < word.size(); ++j) {
                    if(input[i + j] != word[j]) {
                        matched = false;
                        break;
                    }
                }

                if(matched) {
                    input.replace(input.cbegin() + i, input.cbegin() + i + word.size(), word.size(),'*');
                }
            }

            return input;
        }
    }
}