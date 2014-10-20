#ifndef EPOLLER_H_
#define EPOLLER_H_

#include "event_manager.h"

struct epoll_event;

namespace io {

class Epoller : public EventManager {
  public:
    Epoller()
        : ep_fd_(INVALID_FD) {
    }
    virtual ~Epoller();

    virtual void Init();
    virtual void Loop();
    virtual bool LoopInAnotherThread();
    virtual void Stop();

    virtual bool Add(Event* ev);
    virtual void Mod(Event* ev);
    virtual void Del(const Event& ev);

  private:
    int ep_fd_;

    // no need lock.
    typedef std::map<int, Event*> EvMap;
    EvMap ev_map_;

    const static uint32 kTriggerNumber = 128;
    std::vector<epoll_event> events_;

    scoped_ptr<StoppableThread> loop_pthread_;

    uint32 ConvertEvent(uint8 event);

    DISALLOW_COPY_AND_ASSIGN(Epoller);
};
}

#endif
