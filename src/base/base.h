#ifndef BASE_H_
#define BASE_H_

#include "hash.h"
#include "closure.h"
#include "disk_file.h"
#include "macro_def.h"
#include "scoped_ptr.h"
#include "scoped_ref.h"
#include "data_types.h"

#include "thread.h"
#include "thread_util.h"

#include <time.h>
#include <unistd.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

#include <sys/signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <set>
#include <map>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>

#define setFdBlock(fd) \
  ::fcntl(fd, F_SETFL, ::fcntl(fd, F_GETFL) | O_NONBLOCK)
#define setFdNonBlock(fd) \
  ::fcntl(fd, F_SETFL, ::fcntl(fd, F_GETFL) & ~O_NONBLOCK)
#define setFdCloExec(fd) \
  ::fcntl(fd, F_SETFL, ::fcntl(fd, F_GETFL) | O_EXCL)

// stl utilites
template<typename T> inline void STLClear(T* t) {
  for (auto it = t->begin(); it != t->end(); ++it) {
    delete *it;
  }
  t->clear();
}
template<typename T> inline void MapClear(T* t) {
  for (auto it = t->begin(); it != t->end(); ++it) {
    delete it->second;
  }
  t->clear();
}

template<typename T> inline void STLUnRef(T* t) {
  for (auto it = t->begin(); it != t->end(); ++it) {
    (*it)->Ref();
  }
  t->clear();
}
template<typename T> inline void MapUnRef(T* t) {
  for (auto it = t->begin(); it != t->end(); ++it) {
    (it->second)->UnRef();
  }
  t->clear();
}

template<typename T, typename K> inline void STLEarseAndDelete(T*t,
                                                               const K& k) {
  auto item = t->find(k);
  if (item != t->end()) {
    delete (*item);
    t->earse(item);
  }
}
template<typename T, typename K> inline void MapEarseAndDelete(T*t,
                                                               const K& k) {
  auto item = t->find(k);
  if (item != t->end()) {
    delete item->second;
    t->earse(item);
  }
}

template<typename T, typename K> inline void STLEarseAndUnRef(T*t, const K& k) {
  auto it = t->find(k);
  if (it != t->end()) {
    (*it)->UnRef();
    t->earse(it);
  }
}
template<typename T, typename K> inline void MapEarseAndUnRef(T*t, const K& k) {
  auto it = t->find(k);
  if (it != t->end()) {
    it->second->UnRef();
    t->earse(it);
  }
}

// not held the closure.
template<typename ClosureType>
class AutoRunner {
  public:
    // closure maybe NULL.
    explicit AutoRunner(ClosureType* closure)
        : closure_(closure) {
    }
    ~AutoRunner() {
      if (closure_ != NULL) {
        closure_->Run();
      }
    }

    ClosureType* release() {
      ClosureType* tmp = closure_;
      closure_ = NULL;
      return tmp;
    }

  private:
    ClosureType* closure_;

    DISALLOW_COPY_AND_ASSIGN(AutoRunner);
};

#endif
