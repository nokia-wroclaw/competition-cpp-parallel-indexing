competition-cpp-parallel-indexing
=================================

Parallel Indexing Cpp Competition
July 2014
Kacper Kokoszka, Bartosz Szurgot

Info: README.md has to be viewed in raw version for proper display

Task:
Implementation of collection with simple API:
- search(word) returns list of files containing provided word
- index(file) - places new file in collection
- handle n searching (8 threads) and m (2 threads) indexing clients
- application has to handle any number of files/words

Target:
- fast access to collection
- multithread safety
- high responsiveness (no unnecessary blocking)

Tools:
- C++ 14 (gcc-4.9; clang-3.4 - available on wrlinb29.emea.nsn-net.net in /opt/ directory, clang-2.8 for now)
- large text files available at location: wrlinb29.emea.nsn-net.net -> path: /var/fpwork/comp-cpp-par/ (approximately 100 M unique words)
- full C++14 (ok, ok - C++1y) is at your disposal
- no external libraries are allowed

File format:
- text files
- one word per line
- line endings format is not specified

Testing:
- 60 seconds of pseudo random search and index queries
- the best result out of 10 runs is taken
- testing machine: wrlinb29.emea.nsn-net.net

Winning criteria:
Sum of number of handled (finished) queries, performed by all clients + total
number of files found, by queries.
Important: each solution will be checked manually in order to avoid cheating.

Allowed modifications:
- everything under Impl/ directory (both creating new files and modifying existing ones)
- CMakeLists.txt: adding new files, extending compilation and linking flags
- Impl/* contains example implementation (terrible performance, but working)
- types from types.hpp can be changed (like FilesList)

How to:
- run cmake: in build dir 'cmake <path_to_cmakelist.txt> [-G Ninja]' (you can try ninja instead of make)
- use word_list_generator:
    + <seed> - seed for generator
    + <number_of_outputs> - amount of in_files for benchmark
    + <words_per_file> - amount of words in each in_file
    + <in_file_1> ... <in_file_N> - dictionaries to generate in_files from
    + example call: ./word_list_generator 60 20 1000 ../simple_test_data/pl_10k.txt (you have much bigger dictionaries at location provided in Tools section)
- run benchmark:
    + <query-file> - query file generated by word_list_generator named 'queries.txt'
    + <benchmark-seconds> - testing period
    + <in-file-1> ... <in-file-N> - in_files generated by word_list_generator named dict_[number].txt
    + example call: ./benchmark queries.txt 10 dict_*
