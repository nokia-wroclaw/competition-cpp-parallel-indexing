#include <set>
#include <vector>
#include <fstream>
#include "MyIndex.hpp"
#include "readFileAsLines.hpp"

namespace Impl
{

FilesList MyIndex::filesContainingWord(std::string const& word)
{
  std::lock_guard<std::mutex> guard{mutex_};
  std::set<std::string>       uniqueFiles;
  for(auto const& e: index_)
    if(e.first==word)
      uniqueFiles.insert(e.second);
  return FilesList{ begin(uniqueFiles), end(uniqueFiles) };
}


IndexingStatus MyIndex::addToIndex(std::string fileName)
{
  std::lock_guard<std::mutex> guard{mutex_};
  const auto words = readFileAsLines(fileName);
  for(auto const& w: words)
    index_.push_back( Entry{w, fileName} );
  return true;
}

}
