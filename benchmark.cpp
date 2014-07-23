#include <memory>
#include <vector>
#include "Index.hpp"
#include "buildIndex.hpp"
#include "Reader.hpp"

constexpr unsigned writersCount = 2;
constexpr unsigned readersCount = 10;

int main()
{
  IndexShPtr index = buildIndex();

  std::vector<Reader> readers;
}
