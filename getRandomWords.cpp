#include <random>
#include <fstream>
#include <unordered_set>
#include "getRandomWords.hpp"

namespace
{
using WordSet = std::unordered_set<std::string>;

template<typename PRNG>
void addRandomWordsFromFile(WordSet& words, std::string const& file, PRNG& prng)
{
  std::ifstream infile;
  infile.open(file);
  if(not infile.is_open())
    throw std::runtime_error{"unable to open file: " + file};

  std::string line;
  while( std::getline(infile, line) )
    if( prng()==0 )
      words.insert(line);
}
}

std::vector<std::string> getRandomWords(std::vector<std::string> const& files, unsigned seed)
{
  std::unordered_set<std::string>         words;
  std::mt19937_64                         gen{seed};
  std::uniform_int_distribution<unsigned> dist{0, 9};
  auto                                    prng = [&]{ return dist(gen); };
  for(auto const& f: files)
    addRandomWordsFromFile(words, f, prng);
  return { begin(words), end(words) };
}
