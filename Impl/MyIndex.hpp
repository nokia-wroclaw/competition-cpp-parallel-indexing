#pragma once

#include <list>
#include <mutex>
#include "Index.hpp"

namespace Impl
{

// the single worst implementation, within the known universe. an example
// that implements given functionality - just does this terrible. do a better
// job instead! :)
struct MyIndex final: public Index
{
  virtual FilesList filesContainingWord(std::string const& word) override;
  virtual IndexingStatus addToIndex(std::string fileName) override;

private:
  using Entry = std::pair<std::string, std::string>;    // word + file
  std::mutex       mutex_;
  std::list<Entry> index_;
};

}
