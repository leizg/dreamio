#ifndef ECHO_SERVER_H_
#define ECHO_SERVER_H_

#include "base/base.h"

namespace io {
class TcpServer;
class EventManager;
}

namespace test {
class EchoProtocol;

class EchoServer {
  public:
    explicit EchoServer(uint32 worker);
    ~EchoServer();

    bool Init(const std::string& ip, uint16 port);

    void loop(bool in_another_thread = true);

  private:
    uint32 worker_;
    scoped_ptr<EchoProtocol> protocol_;

    scoped_ptr<io::EventManager> ev_mgr_;
    scoped_ptr<io::TcpServer> server_;

    DISALLOW_COPY_AND_ASSIGN(EchoServer);
};
}
#endif /* ECHO_SERVER_H_ */
