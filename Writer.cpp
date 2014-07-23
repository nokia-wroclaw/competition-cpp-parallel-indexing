#include <random>
#include <algorithm>
#include <cassert>

#include "Writer.hpp"

namespace
{
auto shuffleFiles(Writer::FilesList files)
{
  std::mt19937 prng;
  std::shuffle( begin(files), end(files), prng );
  return files;
}
}

Writer::Writer(IndexShPtr const& index, FilesList files, unsigned seed):
  index_{index},
  files_{ shuffleFiles( std::move(files) ) },
  stop_{false},
  indexed_{0},
  th_{&Writer::threadLoop, this}
{ }


void Writer::threadLoop()
{
  while( not stop_ && not files_.empty() )
  {
    auto file = randomFile();
    assert(index_);
    index_->addToIndex( std::move(file) );
    ++indexed_;
  }
}

std::string Writer::randomFile()
{
  assert( not files_.empty() );
  auto tmp = std::move( files_.back() );
  files_.pop_back();
  return tmp;
}
