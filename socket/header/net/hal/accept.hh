#pragma once

#include "net/hal/socket.hh"

namespace flp::Net {

enum class AcceptFlags {
  NonBlock = SOCK_NONBLOCK,
  NonBlocking = NonBlock,

  CLOEXEC = SOCK_CLOEXEC,
};

enum class AcceptError {
  Again = EAGAIN,
  WouldBlock = EWOULDBLOCK,

  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,

  ConnAborted = ECONNABORTED,

  Fault = EFAULT,

  Intr = EINTR,
  Interrupted = Intr,

  Inval = EINVAL,
  Invalid = Inval,

  MFile = EMFILE,

  NFile = ENFILE,

  NoBufs = ENOBUFS,
  NoMem = ENOMEM,
  NoMemory = NoMem,

  NotSock = ENOTSOCK,

  OpNotSupp = EOPNOTSUPP,
  OpNotSupported = OpNotSupp,
  OperationNotSupp = OpNotSupp,
  OperationNotSupported = OpNotSupp,

  Perm = EPERM,

  Proto = EPROTO,

  // Errors for the new socket may also occur, including protocol specific errors

  ProtoNoSupport = EPROTONOSUPPORT,
  ProtocolNotSupported = ProtoNoSupport,
};

void foo() {
  const auto addr_size = sizeof(their_addr);
  const auto acc_res = accept(s, (sockaddr*)&client_addr, &addr_size);
  // VERIFY(acc_res != -1, "... {} ...", errno);
}

}
