#pragma once
#include <string>
#include <memory>
#include "Impl/types.hpp"

struct Index
{
  virtual ~Index() = default;

  virtual Impl::FilesList filesContainingWord(std::string const& word) = 0;
  virtual void addToIndex(std::string fileName) = 0;
};

std::unique_ptr<Index> buildIndex();
