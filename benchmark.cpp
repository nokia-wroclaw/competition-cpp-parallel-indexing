#include <chrono>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

#include "Index.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "buildIndex.hpp"
#include "getRandomWords.hpp"


namespace
{
constexpr unsigned         writersCount{2};
constexpr unsigned         readersCount{10};
const std::chrono::seconds benchmarkLength{1};


auto filesList(int argc, char** argv)
{
  std::vector<std::string> files;
  for(int i=1; i<argc; ++i)
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


template<typename ...Args>
auto readWords(Args const&... args)
{
    return std::make_shared<std::vector<std::string>>( getRandomWords(args...) );
}
} // nnamed namespace


int main(int argc, char** argv)
{
  try
  {
    if(argc<1+1)
    {
      std::cerr << argv[0] << " <file1> <file2> ... <fileN>" << std::endl;
      return 1;
    }

    std::cout << "preparing random queries sets" << std::endl;
    const auto files   = filesList(argc, argv);
    const auto words   = readWords(files, argc);
    const auto index   = IndexShPtr{ buildIndex() };
    std::cout << "building readers" << std::endl;
    const auto readers = make<Reader>(readersCount, index, words);
    std::cout << "building writers" << std::endl;
    const auto writers = make<Writer>(writersCount, index, files);

    std::cout << "benchmarking..." << std::endl;
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
