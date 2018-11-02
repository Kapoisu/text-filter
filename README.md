# text-filter

This is a text filter which receive UTF-8 encoded text as input.

## Getting Started

When you execute the program, you'd see a terminal-liked console interface:
```bash
Enter "help" to see the manual

$ text-filter
```
You can enter a command to execute one of the following operations:
- add
- filter
- reset
- test (for development purposes)
- quit

For example, enter **add \<_pattern_\>** to add a string you want to block:
```bash
$ text-filter add gengar
add word: gengar
```
Entering multiple patterns at once is also supported:
```bash
$ text-filter add x y z
add word: x
add word: y
add word: z
```
After you've added all the patterns you want to block, you can enter **filter \<_input_\>**":
```bash
$ text-filter filter: gengar is cute
input: gengar is cute
output: ****** is cute
```
Then you'd see the "gengar" part replaced by asterisk(*).

## Design
Currently [Aho-Corasick](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm) algorithm is used for filtering the text.

![alt text](https://upload.wikimedia.org/wikipedia/commons/6/62/Ahocorasick.svg)

To make all things work, follow the steps below:

### Build the "trie" structure
In the picture above, each path from the root node to a blue node represents a string pattern. The black arrows represent the parent→child relationship. Use patterns added to our filter to construct the trie. As you can see, **a**, **ab**, **bab**, **bc**, **bca**, **c**, **caa** are patterns inside the structure.
### Add suffix links
The blue arrows redirect us to another path followed by other patterns whose prefix is the longest suffix of our current pattern whenever we encounter a character mismatch. For example, if we fail to match a pattern "discourage" at 'r', we might be redirected to the 'r' node of another path(c→o→u→r). This implies that there must be patterns with prefix "cour-" inside the structure. We can continue matching these patterns without checking 'c', 'o', 'u', 'r' again. 
### Add in-dict suffix links
The green arrows redirect us to an in-dict node represents the end of a pattern which match the suffix of our current pattern). The reason we must check this link in each iteration is that if we fail to match any patterns which contains the suffix of our current pattern, we take the risk of bypassing the patterns with **non-longest** suffix of our current pattern.
### Match the input
Iterate our input one by one, and use a pointer to track the current node in the trie. In each iteration, check if the current node has a child node that match the next character. If one found, follow the parent-to-child path; otherwise, follow the suffix link. Then check if the current node is an in-dict node and also check if there is an in-dict suffix link. If there is one, replace the [current iterator position - current node depth, current iterator position] part of the input.

(Actually we do not need to check the in-dict suffix if the current node is an in-dict node because our application is to filter text, blocking the pattern with the longest suffix also blocks the ones with non-longest suffix.)
## Analysis
### Time Complexity
The time complexity of the algorithm is **O(m + n + l)**, where **m** is the number of output matches, **n** is the length of the input text, and **l** is the length of each patterns. In this application, we only need to find one match in each iteration at most, where **m** is either 0 or 1. Therefore, the actual time complexity is **O(n + l)**.
### Space Complexity
The space complexity varies from the composition of patterns. The worst case is **O(n)**, where **n** is the total length of all patterns (in this case, any of which is not a substring of others).

## Test
I used http://www.randomtextgenerator.com/ to generate test cases because it produced meaningful vocabularies randomly. If I generated random characters and constructed them to string literals by myself, there would have been very low probabiliy matching patterns with a decent length. In addition, filter patterns were downloaded from the internet (something like "The Most Common Used 1000 Vocabularies".)

At the beginning, I'd tried to use C++ to write the test cases generating program; however, it is quite difficult to do network programming without a proper third-party library. I ended up writing a C# program - which is excluded from the repository - to finish the task.
## Performance
