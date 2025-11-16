#pragma once

namespace flp::Net {

enum class ShutdownHow {
  RD = SHUT_RD,
  WR = SHUT_WR,
  RDWR = SHUT_RDWR,

  DisallowReceive = RD,
  DisallowSend = WR,
  Close = RDWR,
};

enum class ShutdownError {
  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
  BadFileDescriptor = BadFile,

  Inval = EINVAL,
  Invalid = Inval,
  InvalidArgument = Invalid,
  
  NotConn = ENOTCONN,
  NotConnected = NotConn,

  NotSock = ENOTSOCK,
  NotSocket = NotSock,
};

void foo(ShutdownHow how) {
  shutdown(s, how);
  // still need to `close(s)` to dispose of the file descriptor.
}

}
