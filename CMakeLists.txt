project(competition-cpp-parallel-indexing)
set(CMAKE_CXX_COMPILER "g++-4.9")

set(common_flags "-Wall -Werror -I${CMAKE_SOURCE_DIR} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${common_flags} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${common_flags} -s")

set(sources
     benchmark.cpp
     Impl/MyIndex.cpp
   )

add_executable(benchmark ${sources})
