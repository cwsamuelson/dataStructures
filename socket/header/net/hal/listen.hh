#pragma once

namespace flp::Net {

enum class ListenError {
  AddrInUse = EADDRINUSE,
  AddressInUse = AddrInUse,

  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
 
  NotSock = ENOTSOCK,
  NotSocket = NotSock,
 
  OPNotSupp = EOPNOTSUPP,
  OPNotSupported = OPNotSupp,
  OperationNotSupported = OPNotSupported,
};

void foo() {
  const auto list_res = listen(s, 10);
  // VERIFY(list_res != -1, "... {} ...", errno);
}

}
