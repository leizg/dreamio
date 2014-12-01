#include <glog/logging.h>
#include <google/gflags.h>

#include "echo_server.h"

DEFINE_string(ip, "0.0.0.0", "ip for echo server");
DEFINE_int32(port, 8888, "port for echo server");
DEFINE_int32(worker, 4, "number of worker thread");

int main(int argc, char* argv[]) {
  ::google::InitGoogleLogging(argv[0]);
  ::google::ParseCommandLineFlags(&argc, &argv, true);

  test::EchoServer serv(FLAGS_worker);
  if (!serv.Init(FLAGS_ip, FLAGS_port)) {
    return -1;
  }

  serv.loop();

  return 0;
}
