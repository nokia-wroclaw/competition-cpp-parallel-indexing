project(competition-cpp-parallel-indexing)

set(CMAKE_CXX_COMPILER "g++-4.9")

set(common_flags "-Wall -Werror -I${CMAKE_SOURCE_DIR} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${common_flags} -g3 -ggdb -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${common_flags} -s")

add_executable(benchmark
  readFileAsLines.cpp
  benchmark.cpp
  Reader.cpp
  Writer.cpp
  Impl/MyIndex.cpp
  Impl/buildIndex.cpp
)

target_link_libraries(benchmark
  pthread
)

add_executable(word_list_generator
  word_list_generator.cpp
  readFileAsLines.cpp
)
