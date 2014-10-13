#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include "base/base.h"

#define EV_READ (1<<0)
#define EV_WRITE (1<<1)
#define EV_ERROR (1<<2)

struct Event {
  int fd;
  void* arg;
  uint8 event;
  void (*cb)(int fd, void* arg, uint8 revent, const TimeStamp& time_stamp);
};

namespace io {
class TimerQueue;

class EventManager {
 public:
  virtual ~EventManager();

  virtual bool Init() = 0;
  virtual void Loop() = 0;
  virtual bool LoopInAnotherThread() = 0;
  virtual void Stop() = 0;

  virtual bool Add(Event* ev) = 0;
  virtual void Mod(Event* ev) = 0;
  virtual void Del(const Event& ev) = 0;

  bool inLoopThread() const {
    return ::pthread_equal(loop_tid_, ::pthread_self());
  }
  void assertInLoopThread() const {
    CHECK(inLoopThread());
  }
  void runInLoop(Closure* cb);
  void handleClosure();

  TimerQueue* getTimerQueue() const {
    return timer_queue_.get();
  }

 protected:
  EventManager();
  // must be called after initialized successfully.
  bool InitPipe();

  bool stop_;
  pthread_t loop_tid_;

 private:
  int event_fd_[2];
  Mutex mutex_;
  std::deque<Closure*> cb_queue_;
  scoped_ptr<TimerQueue> timer_queue_;

  DISALLOW_COPY_AND_ASSIGN(EventManager);
};

EventManager* CreateEventManager();

}

#endif /* EVENT_MANAGER_H_ */