#pragma once

namespace flp::Net {

enum class How {
  DisallowReceive = 0,
  DisallowSends = 1,
  Close = 2,
};

void foo(How how) {
  shutdown(s, how);
  // still need to `close(s)` to dispose of the file descriptor.
}

}
