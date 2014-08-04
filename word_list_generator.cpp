#include <string>
#include <vector>
#include <random>
#include <utility>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include "readFileAsLines.hpp"

using std::cout;
using std::cerr;
using std::endl;


constexpr auto numberedWordEveryIteration = 23;
constexpr auto queryEveryIteration        = 9;


auto readAllFiles(int argc, char** argv)
{
  std::vector<std::string> out;
  for(int i=4; i<argc; ++i)
  {
    auto filename = argv[i];
    cout << "reading file " << filename << endl;
    auto words = readFileAsLines(filename);
    out.reserve( out.size() + words.size() );
    for(auto& w: words)
      out.push_back( std::move(w) );
  }
  return out;
}


template<typename Dict, typename Prng>
void generateFile(std::string const& filename, const unsigned wordsCount, Dict const& dict, Prng& prng, std::unordered_set<std::string>& queries)
{
  cout << "generating file " << filename << "..." << endl;
  std::ofstream os(filename);
  if( not os.is_open() )
    throw std::runtime_error{"unable to open file for writing: " + filename};

  for(unsigned i=0; i<wordsCount; ++i)
  {
    const auto addNumber = (i % numberedWordEveryIteration) == 0;
    auto       word      = dict[prng()] + ( addNumber ? std::to_string(prng()) : "" );
    os << word << "\n";
    if( (i % queryEveryIteration) == 0 )
      queries.insert( std::move(word) );
  }
}


void writeQueriesToFile(std::string const& filename, std::unordered_set<std::string> const& queries)
{
  cout << "writing queries to file " << filename << "..." << endl;
  std::ofstream os(filename);
  if( not os.is_open() )
    throw std::runtime_error{"unable to open file for writing: " + filename};

  for(auto const& q: queries)
    os << q << '\n';
}



int main(int argc, char** argv)
{
  try
  {
    if( argc <= 1+3 )
    {
      cerr << argv[0] << " <seed> <number_of_outputs> <words_per_file> <in_file_1> ... <in_file_N>" << endl;
      return 1;
    }

    const auto seed         = atoi(argv[1]);
    const auto filesCount   = atoi(argv[2]);
    const auto wordsPerFile = atoi(argv[3]);
    const auto dictionary   = readAllFiles(argc, argv);

    if( dictionary.empty() )
      throw std::runtime_error{"given files did not contain a single word"};
    if( filesCount <= 0 )
      throw std::runtime_error{"files count must be positive"};
    if( wordsPerFile <= 0 )
      throw std::runtime_error{"number of words per file must be positive"};

    std::uniform_int_distribution<unsigned> dist(0, dictionary.size()-1);
    std::mt19937_64                         gen(seed);
    auto                                    prng = [&]{ return dist(gen); };
    std::unordered_set<std::string>         queries;

    for(int i=0; i<filesCount; ++i)
      generateFile( "dict_" + std::to_string(i) + ".txt", wordsPerFile, dictionary, prng, queries );

    writeQueriesToFile( "queries.txt", queries );

    cout << "all done" << endl;
  }
  catch(std::exception const& ex)
  {
    cerr << argv[0] << ": ERROR: " << ex.what() << endl;
  }
}
