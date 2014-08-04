#pragma once

#include <mutex>
#include <memory>
#include <stdexcept>
#include <condition_variable>


class Event
{
public:
  Event():
    blocked_{true}
  { }

  void set()
  {
    {
      Lock lock{m_};
      blocked_ = false;
    }
    unblocked_.notify_all();
  }

  void clear()
  {
    Lock lock{m_};
    blocked_ = true;
  }

  void wait() const
  {
    Lock lock{m_};
    unblocked_.wait(lock, [&]{ return not blocked_; });
  }

private:
  using Lock = std::unique_lock<std::mutex>;

  bool                            blocked_;
  mutable std::mutex              m_;
  mutable std::condition_variable unblocked_;
};


using EventShPtr = std::shared_ptr<Event>;
