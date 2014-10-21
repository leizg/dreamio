#ifndef CONNECTOR_H_
#define CONNECTOR_H_

#include "tcp_client.h"

namespace io {

class Connector : public TcpClient::Connector {
  public:
    Connector() {
    }
    virtual ~Connector() {
    }

    // return INVALID_FD if connected failed.
    // timeout: wait for seconds.
    virtual int Connect(const std::string& ip, uint16 port,
                        uint32 time_out) const;

  private:
    int CreateSocket() const;

    // return true iif connected successfully.
    bool WaitForConnected(int fd, uint32 time_out) const;

    DISALLOW_COPY_AND_ASSIGN(Connector);
};
}

#endif /* CONNECTOR_H_ */
