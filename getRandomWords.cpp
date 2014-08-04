#include <random>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "getRandomWords.hpp"
#include "readFileAsLines.hpp"

namespace
{
using WordSet = std::unordered_set<std::string>;

template<typename PRNG>
void addRandomWordsFromFile(WordSet& words, std::string const& file, PRNG& prng)
{
  auto newWords = readFileAsLines(file);
  for(auto const& w: newWords)
    if( prng()==0 )
      words.insert(w);
}
}

std::vector<std::string> getRandomWords(std::vector<std::string> const& files, unsigned seed)
{
  std::unordered_set<std::string>         words;
  std::mt19937_64                         gen{seed};
  std::uniform_int_distribution<unsigned> dist{0, 9};
  auto                                    prng = [&]{ return dist(gen); };
  for(auto const& f: files)
  {
    std::cout << "  -> adding random words from file " << f << std::endl;
    addRandomWordsFromFile(words, f, prng);
  }
  return { begin(words), end(words) };
}
