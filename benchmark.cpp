#include <chrono>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

#include "Index.hpp"
#include "Event.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "buildIndex.hpp"
#include "readFileAsLines.hpp"


namespace
{
constexpr unsigned writersCount{2};
constexpr unsigned readersCount{10};


auto filesList(int argc, char** argv)
{
  std::vector<std::string> files;
  for(int i=3; i<argc; ++i)
    files.emplace_back(argv[i]);
  return files;
}


template<typename T, typename ...Args>
auto make(const unsigned count, Args... args)
{
  std::vector<std::unique_ptr<T>> c;
  for(unsigned i=0; i<count; ++i)
    c.push_back( std::make_unique<T>(args..., i) );
  return c;
}


auto readQueryWords(std::string const& queryFile)
{
    return std::make_shared<std::vector<std::string>>( readFileAsLines(queryFile) );
}
} // unnamed namespace


int main(int argc, char** argv)
{
  try
  {
    if(argc<1+3)
    {
      std::cerr << argv[0] << " <query-file> <benchmark-seconds> <in-file-1> <in-file-2> ... <in-file-N>" << std::endl;
      return 1;
    }

    const auto benchmarkLength = std::chrono::seconds{ atoi(argv[2]) };
    const auto start = std::make_shared<Event>();
    std::cout << "preparing random queries sets" << std::endl;
    const auto files = filesList(argc, argv);
    const auto words = readQueryWords(argv[1]);
    const auto index = IndexShPtr{ buildIndex() };
    std::cout << "building readers" << std::endl;
    const auto readers = make<Reader>(readersCount, start, index, words);
    std::cout << "building writers" << std::endl;
    const auto writers = make<Writer>(writersCount, start, index, files);

    std::cout << "benchmarking..." << std::endl;
    start->set();
    std::this_thread::sleep_for(benchmarkLength);

    uint64_t indexed{0};
    for(auto const& w: writers)
      indexed += w->filesIndexed();

    uint64_t reads{0};
    uint64_t hits{0};
    for(auto const& r: readers)
    {
      reads += r->readsCount();
      hits  += r->hitsCount();
    }

    std::cout << "summary report:" << std::endl;
    std::cout << "  * " << indexed << " files indexed by writers" << std::endl;
    std::cout << "  * " << reads   << " queries performed by readers" << std::endl;
    std::cout << "  * " << hits    << " files found by readers" << std::endl;
    std::cout << "your score is: " << reads + hits << std::endl;

    std::cout << "waiting for all threads to finish..." << std::endl;
    // following stops are not strictly necessary, but they speed up shutting down
    for(auto& w: writers)
      w->stop();
    for(auto& r: readers)
      r->stop();
  }
  catch(std::exception const& ex)
  {
    std::cerr << "EXCEPTION: " << typeid(ex).name() << ": " << ex.what() << std::endl;
    return 2;
  }
}
