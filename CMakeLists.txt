project(competition-cpp-parallel-indexing)

set(CMAKE_CXX_COMPILER "g++-4.9")

set(common_flags "-Wall -Werror -I${CMAKE_SOURCE_DIR} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${common_flags} -g3 -ggdb -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${common_flags} -s")

add_executable(benchmark
  benchmark.cpp
  Reader.cpp
  Writer.cpp
  Impl/MyIndex.cpp
  Impl/buildIndex.cpp
)

add_executable(files_generator
  files_generator.cpp
)
