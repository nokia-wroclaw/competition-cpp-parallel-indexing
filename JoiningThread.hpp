#pragma once

#include <thread>
#include <utility>

struct JoiningThread
{
  template<typename ...Args>
  explicit JoiningThread(Args&&... args):
    th_{ std::forward<Args>(args)... }
  { }

  ~JoiningThread()
  {
    if( th_.joinable() )
      th_.join();
  }

  JoiningThread(JoiningThread&&) = default;
  JoiningThread& operator=(JoiningThread&&) = default;

  std::thread*       operator->()       { return &th_; }
  std::thread const* operator->() const { return &th_; }

private:
  std::thread th_;
};
