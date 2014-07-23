#pragma once

#include <vector>
#include <string>
#include <atomic>
#include <memory>
#include <cinttypes>
#include "Index.hpp"
#include "JoiningThread.hpp"

struct Writer
{
  using FilesList = std::vector<std::string>;
  using Words     = std::vector<std::string>;

  Writer(IndexShPtr const& index, FilesList files, unsigned seed);
  ~Writer(void) { stop(); }

  void stop() { stop_ = true; }
  uint64_t filesIndexed() { return indexed_; }

private:
  void threadLoop();

  std::string randomFile();

  IndexShPtr            index_;
  FilesList             files_;
  std::atomic<bool>     stop_;
  std::atomic<uint64_t> indexed_;
  JoiningThread         th_;
};


using WriterPtr = std::unique_ptr<Writer>;
