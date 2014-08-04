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
- C++ 14 (gcc-4.9; clang-3.4)
- large text files available at location: unknown for now
- full C++14 (ok, ok - C++1y) is at your disposal
- no external libraries are allowed

File format:
- text files
- one word per line
- line endings format is not specified

Testing:
60 seconds of pseudo random search and index queries.

Winning criteria:
Maximum amount of handled (finished):
- number of performed queries
- number of matches found

Allowed modifications:
- everything under Impl/ directory (both creating new files and modifying existing ones).
- CMakeLists.txt: adding new files, extending compilation and linking flags.
- Impl/* contains example implementation (terrible performance, but working).
