#include <set>
#include <vector>
#include <fstream>
#include "MyIndex.hpp"

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


namespace
{
auto getWordsFromFile(std::string const& file)
{
  std::ifstream infile;
  infile.open(file);
  if(not infile.is_open())
    throw std::runtime_error{"unable to open file: " + file};

  std::vector<std::string> words;
  std::string              line;
  while( std::getline(infile, line) )
    words.push_back(line);

  return words;
}
}

IndexingStatus MyIndex::addToIndex(std::string fileName)
{
  std::lock_guard<std::mutex> guard{mutex_};
  const auto words = getWordsFromFile(fileName);
  for(auto const& w: words)
    index_.push_back( Entry{w, fileName} );
  return true;
}

}
