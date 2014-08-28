#pragma once

#include <atomic>
#include <random>
#include <memory>
#include <cinttypes>
#include "Index.hpp"
#include "Event.hpp"
#include "JoiningThread.hpp"

struct Reader
{
  using Word = std::vector<std::string>;
  using Words = std::vector<Word>;
  using WordsShPtr = std::shared_ptr<Words>;

  Reader(EventShPtr const& start, IndexShPtr const& index, WordsShPtr const& words, unsigned seed);
  ~Reader(void) { stop(); }

  void stop()
  {
    stop_ = true;
    start_->set();
  }
  uint64_t readsCount() { return reads_; }
  uint64_t hitsCount() { return hits_; }

private:
  void threadLoop();
  Word const& randomWord();

  std::mt19937                                    gen_;
  std::uniform_int_distribution<Words::size_type> dist_;

  IndexShPtr            index_;
  WordsShPtr            words_;
  std::atomic<bool>     stop_;
  std::atomic<uint64_t> reads_;
  std::atomic<uint64_t> hits_;
  EventShPtr            start_;
  JoiningThread         th_;
};


using ReaderPtr = std::unique_ptr<Reader>;
