#pragma once
#include <memory>
#include "Index.hpp"

using IndexPtr   = std::unique_ptr<Index>;
using IndexShPtr = std::shared_ptr<Index>;

IndexPtr buildIndex();
