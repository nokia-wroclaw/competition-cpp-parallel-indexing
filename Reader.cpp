#include <unordered_set>
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
  while(not stop_)
  {
    auto const& word  = randomWord();
    const auto  files = index_->filesContainingWord(word);
    assert( ensureListIsUnique(files) );
    ++reads_;
    hits_ += files.size();
  }
}
