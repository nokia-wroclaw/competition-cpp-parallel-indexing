#include "buildIndex.hpp"
#include "MyIndex.hpp"

IndexPtr buildIndex()
{
  return std::make_unique<Impl::MyIndex>();
}
