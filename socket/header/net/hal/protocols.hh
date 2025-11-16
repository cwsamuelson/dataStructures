#pragma once

namespace flp::Net {

// https://man7.org/linux/man-pages/man5/protocols.5.html
// https://man7.org/linux/man-pages/man3/getprotoent.3.html

// The protocol interface is how you're 'supposed' to get the level ID number when using the [gs]etsockopt interface.

void foo() {
  // protoent *getprotoent(void);
  // protoent *getprotobyname(const char *name);
  // protoent *getprotobynumber(int proto);
  // void setprotoent(int stayopen);
  // void endprotoent(void);
}

}
