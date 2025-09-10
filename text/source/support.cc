#include "text/support.hh"

namespace flp {

size_t strlen(const char* cstring) noexcept {
  if (cstring == nullptr) {
    return 0;
  }

  size_t length{};

  while (*cstring != '\0') {
    ++cstring;
    ++length;
  }

  return length;
}

}
