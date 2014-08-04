#include <unordered_set>
#include <cassert>
#include "Reader.hpp"

namespace
{
template<typename C>
auto maxIndex(C const& c)
{
  if( not c.empty() )
    return c.size()-1u;
  return typename C::size_type{0u};
}
}


Reader::Reader(EventShPtr const& start, IndexShPtr const& index, WordsShPtr const& words, unsigned seed):
  gen_{seed},
  dist_{0, maxIndex(*words)},
  index_{index},
  words_{words},
  stop_{false},
  reads_{0},
  hits_{0},
  start_{start},
  th_{&Reader::threadLoop, this}
{
  assert( th_->joinable() );
}


namespace
{
template<typename T>
bool ensureListIsUnique(T const& t)
{
  std::unordered_set<std::string> tmp{ begin(t), end(t) };
  return tmp.size() == t.size();
}
}

void Reader::threadLoop()
{
  start_->wait();
  while(not stop_)
  {
    auto const& word  = randomWord();
    const auto  files = index_->filesContainingWord(word);
    assert( ensureListIsUnique(files) );
    ++reads_;
    hits_ += files.size();
  }
}


std::string const& Reader::randomWord()
{
  const auto n = dist_(gen_);
  assert( n < words_->size() );
  return (*words_)[n];
}
