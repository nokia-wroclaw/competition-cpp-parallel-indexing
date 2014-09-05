#set(CMAKE_CXX_COMPILER clang++-3.4)
project(competition-cpp-parallel-indexing)

set(CMAKE_CXX_FLAGS         "-Wall -Werror -I${CMAKE_SOURCE_DIR} -std=c++1y")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb -fsanitize=address -pg")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -Os")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${common_flags} -g1 -pg")

if("$ENV{HOSTNAME}" MATCHES "^wrlin[bg].*")
  message(STATUS "NSN's wrling host detected")
  set(CMAKE_CXX_COMPILER "/opt/gcc/linux64/ix86/gcc_4.9.0-rhel6/bin/g++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath=/opt/gcc/linux64/ix86/gcc_4.9.0-rhel6/lib64/")
else()
  set(CMAKE_CXX_COMPILER "g++-4.9")
endif()

add_executable(benchmark
  readFileAsLines.cpp
  benchmark.cpp
  Reader.cpp
  Writer.cpp
  Word.cpp
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
