competition-cpp-parallel-indexing
=================================

Parallel Indexing Cpp Competition
July 2014
Kacper Kokoszka, Bartosz Szurgot

Task:
Implementation of collection with simple API:
- search(word) returns list of files containing provided word
- index(files_list) - places new files in collection.
which will handle n searching and m indexing clients.

Target:
- fast access to collection
- multithred safety
- high responsiveness (no unnecessary blocking)

Tools:
- c++ 14 (gcc-4.9; clang-3.4)
- large text files available at location: unknown for now

Testing:
2 minutes of pseudo random search and index queries.

Winning criteria:
Maximum amount of handled (finished):
- all queries
- search operations results
