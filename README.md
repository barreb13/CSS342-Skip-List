# Skiplist

Goals: Working with dynamic arrays, pointers, doubly linked lists

For this assignment, you will write a Skip List data structure to store integers. 

When searching a Skip List, items can be found in O(log n) time. 
No duplicates are allowed.A SkipList can have multiple levels. 
SkipList of depth 1 is similar to a doubly linked list. All elements are inserted into a single doubly linked list.

When a SkipList has multiple levels, all elements are inserted at level = 0. 50% of those inserted at level = 0, 
are also inserted at level = 1. 50% of those inserted at level = 1 are also inserted at level = 2, and so on.

## Compile and Run

```
./simplecompile.sh
```


### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

- fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- readability-braces-around-statements: allow compact code without `{`
This option is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using 9.0.0
- hicpp-no-array-decay need to use assert
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- hicpp-braces-around-statements: allow compact code without `{` (this option
- cppcoreguidelines-pro-bounds-pointer-arithmetic,
- llvm-header-guard: not using full directory name
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- cppcoreguidelines-special-member-functions: not defining move operator
- hicpp-special-member-functions: not defining move operator
- cppcoreguidelines-owning-memory: not using gsl

## Misc

This file is part of a repository located at
https://github.com/jdelliot/skiplist

