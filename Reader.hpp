#pragma once

#include <atomic>
#include <cinttypes>
#include "JoiningThread.hpp"

struct Reader
{
  Reader();

  void stop() { stop_ = true; }
  uint64_t readsCount() { return reads_; }
  uint64_t hitsCount() { return hits_; }

private:
  void threadLoop();

  std::atomic<bool>     stop_;
  std::atomic<uint64_t> reads_;
  std::atomic<uint64_t> hits_;
  JoiningThread         th_;
};
