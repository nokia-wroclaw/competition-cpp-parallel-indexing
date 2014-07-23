#include <iostream>
#include <cassert>
#include "Reader.hpp"

Reader::Reader(IndexShPtr const& index, WordsShPtr const& words, unsigned seed):
  gen_{seed},
  dist_{0, words->size()},
  index_{index},
  words_{words},
  stop_{false},
  reads_{0},
  hits_{0},
  th_{&Reader::threadLoop, this}
{
  assert( th_->joinable() );
}

void Reader::threadLoop()
{
  while(not stop_)
  {
    std::cout << "hello thread\n";
  }
}
