#include <iostream>
#include <cassert>
#include "Reader.hpp"

Reader::Reader():
  stop_{false},
  reads_{0},
  hits_{0},
  th_{&Reader::threadLoop, this}
{
  assert( th_->joinable() );
}

void Reader::threadLoop()
{
  std::cout << "hello thread\n";
}
