#include <fmt/format.h>
#include <iostream>
#include <zmq.hpp>

int main(int argc, char *argv[]) {
  zmq::context_t ctx;
  std::string buffer;
  zmq::message_t mess;
  int tab[argc];
  zmq::socket_t sock(ctx, zmq::socket_type::rep);
  sock.bind("tcp://*:8080");
  sock.recv(mess);
  buffer = std::string{static_cast<char *>(mess.data()), mess.size()};
  fmt::print("{}", buffer);
  sock.send(zmq::buffer("DONE"));

  return 0;
}