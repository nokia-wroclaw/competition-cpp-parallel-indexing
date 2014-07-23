#pragma once

#include "Index.hpp"

namespace Impl
{

struct MyIndex: public Index
{
  virtual FilesList filesContainingWord(std::string const& word);
  virtual IndexingStatus addToIndex(std::string fileName);
};

}
