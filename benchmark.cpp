#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

#include "Index.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "buildIndex.hpp"
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


int main(int argc, char** argv)
{
  try
  {
    if(argc<1+1)
    {
      std::cerr << argv[0] << " <file1> <file2> ... <fileN>" << std::endl;
      return 1;
    }

    const auto       files   = filesList(argc, argv);
    const auto       words   = readWords(files, argc);
    const IndexShPtr index   = buildIndex();
    const auto       readers = make<Reader>(readersCount, index, words);
    const auto       writers = make<Writer>(writersCount, index, files);

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
