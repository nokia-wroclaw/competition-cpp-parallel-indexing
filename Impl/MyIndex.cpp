#include "MyIndex.hpp"

namespace Impl
{

FilesList MyIndex::filesContainingWord(std::string const& word)
{
  // TODO
  return {};
}

IndexingStatus MyIndex::addToIndex(std::string fileName)
{
  // TODO
  return {};
}

}


std::unique_ptr<Index> buildIndex()
{
  return std::make_unique<Impl::MyIndex>();
}
