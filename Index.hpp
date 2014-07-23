#pragma once
#include <string>
#include "Impl/types.hpp"

struct Index
{
  Index() = default;
  virtual ~Index() = default;

  Index(Index const&) = delete;
  Index& operator=(Index const&) = delete;

  virtual Impl::FilesList filesContainingWord(std::string const& word) = 0;
  virtual Impl::IndexingStatus addToIndex(std::string fileName) = 0;
};
