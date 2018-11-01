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

For example, enter "add \<pattern\>" to add a string you want to block:
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
After you've added all the patterns you want to block, you can enter "filter \<input\>":
```bash
$ text-filter filter: gengar is cute
input: gengar is cute
output: ****** is cute
```
Then you'd see the "gengar" part replaced by asterisk(*).
