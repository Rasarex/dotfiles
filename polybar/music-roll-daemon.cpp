#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <zmq.hpp>

std::string roll(std::string preroll, size_t roll_by, size_t ret_size,
                 std::string delimiter = "  ") {
  preroll += delimiter;
  std::string retval;
  retval.resize(ret_size);
  for (size_t i = 0; i < ret_size; ++i) {
    retval[i] = preroll[(i + roll_by) % preroll.size()];
  }
  return retval;
}

std::string exec(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

int main(int argc, char const *argv[]) {

  zmq::context_t ctx{1};
  zmq::message_t mess;
  zmq::socket_t sock(ctx, zmq::socket_type::req);
  std::string update_message;
  std::string previous_message = "";
  int i = 0;
  sock.connect("tcp://localhost:8080");
  while (true) {
    update_message = exec("playerctl status 2> /dev/null");
    if (update_message != "Playing\n") {
      sock.send(zmq::buffer(update_message), zmq::send_flags::dontwait);
      sock.recv(mess);
      continue;
    }
    // If status  is Playing this will return something as long as
    // there is metadata on a file
    update_message = exec("playerctl metadata xesam:albumArtist 2> /dev/null");
    update_message.pop_back();
    update_message += " - ";
    update_message += exec("playerctl metadata xesam:title 2> /dev/null");
    update_message.pop_back();

    if (previous_message != update_message) {
      sock.send(zmq::buffer(roll(update_message, i++, 16) + '\n'),
                zmq::send_flags::dontwait);
      sock.recv(mess);
    } else {
      i = 0;
    }
    zmq_sleep(1);
  }
  return 0;
}
