#pragma once

namespace flp::Net {

void foo() {
  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);

  FD_ISSET(fd, &readfds);
}

}
