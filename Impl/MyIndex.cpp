#include "MyIndex.hpp"

namespace Impl
{

FilesList MyIndex::filesContainingWord(std::string const& word)
{
  // TODO
  return {};
}

void MyIndex::addToIndex(std::string fileName)
{
  // TODO
}

}


std::unique_ptr<Index> buildIndex()
{
  return std::make_unique<Impl::MyIndex>();
}
