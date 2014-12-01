#ifndef ECHO_CLIENT_H_
#define ECHO_CLIENT_H_

#include "base/base.h"

namespace io {
class TcpClient;
class EventManager;
}

namespace test {

class EchoClient {
  public:
    explicit EchoClient(uint32 count);
    ~EchoClient();

    bool connect(const std::string& ip, uint16 port);

    void startTest();
    void waitForFinished();

  private:
    scoped_ptr<io::EventManager> ev_mgr_;
    scoped_ptr<io::TcpClient> client_;

    scoped_ptr<StoppableThread> thread_;

    DISALLOW_COPY_AND_ASSIGN(EchoClient);
};
}
#endif /* ECHO_CLIENT_H_ */
