#pragma once

#include "net/hal/fd_set.hh"
#include "net/hal/timeval.hh"

namespace flp::Net {

void foo() {
  timeval tv;
  fd_set readfds;
  tv.tv_sec = 2;
  tv.tv_usec = 500'000;

  FD_ZERO(&readfds);
  FD_SET(STDIN, &readfds);

  select(STDIN + 1, &readfds, nullptr, nullptr, &tv);

  if (FD_ISSET(STDIN, &readfds)) {
    // key pressed!
  } else {
    // timeout
  }
}

}
