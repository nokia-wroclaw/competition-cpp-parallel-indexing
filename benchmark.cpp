#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

#include "Index.hpp"
#include "buildIndex.hpp"
#include "Reader.hpp"
#include "getRandomWords.hpp"

constexpr unsigned writersCount = 2;
constexpr unsigned readersCount = 10;

auto filesList(int argc, char** argv)
{
  std::vector<std::string> files;
  for(int i=1; i<argc; ++i)
    files.emplace_back(argv[i]);
  return files;
}


template<typename ...Args>
auto makeReaders(Args... args)
{
  std::vector<ReaderPtr> readers;
  for(unsigned i=0; i<readersCount; ++i)
    readers.push_back( std::make_unique<Reader>(args..., i) );
  return readers;
}


int main(int argc, char** argv)
{
  try
  {
    if(argc<1+1)
    {
      std::cerr << argv[0] << " <file1> <file2> ... <fileN>" << std::endl;
      return 1;
    }

    const auto files   = filesList(argc, argv);
    const auto words   = std::make_shared<std::vector<std::string>>( getRandomWords(files, argc) );
    IndexShPtr index   = buildIndex();
    const auto readers = makeReaders(index, words);

    // TODO: add writers
    // TODO: add timeout
    // TODO: add results collecting
  }
  catch(std::exception const& ex)
  {
    std::cerr << "EXCEPTION: " << typeid(ex).name() << ": " << ex.what() << std::endl;
    return 2;
  }
}
