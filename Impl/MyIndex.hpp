#pragma once

#include "Index.hpp"

namespace Impl
{

struct MyIndex final: public Index
{
  virtual FilesList filesContainingWord(std::string const& word) override;
  virtual IndexingStatus addToIndex(std::string fileName) override;
};

}
