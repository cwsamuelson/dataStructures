#pragma once

namespace flp::Net {

enum class SendFlags {
  Confirm = MSG_CONFIRM,

  DontRoute = MSG_DONTROUTE,

  DontWait = MSG_DONTWAIT,

  EOR = MSG_EOR,
  EndOfRecord = EOR,

  More = MSG_MORE,

  NoSignal = MSG_NOSIGNAL,

  OOB = MSG_OOB,
  OutOfBand = OOB,

  FastOpen = MSG_FASTOPEN,
};

enum class SendErrors {
  Access = EACCES, // (For UNIX domain sockets, which are identified by pathname)

  WouldBlock = EWOULDBLOCK, // or EAGAIN

  Again = EAGAIN, // (Internet domain datagram sockets)

  Already = EALREADY,

  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
  BadFileDescriptor = BadFile,

  ConnReset = ECONNRESET,
  ConnectionReset = ConnReset,
  Reset = ConnectionReset,

  DestAddrReq = EDESTADDRREQ,
  DestinationAddressRequest = DestAddrReq,

  Fault = EFAULT,

  Intr = EINTR,
  Interrupted = Intr,

  Inval = EINVAL,
  Invalid = Inval,
  InvalidArgument = Invalid,

  IsConn = EISCONN,
  IsConnected = IsConn,

  MsgSize = EMSGSIZE,
  MessageSize = MsgSize,

  NoBufs = ENOBUFS,
  NoBuffers = NoBufs,

  NoMem = ENOMEM,
  NoMemory = NoMem,

  NotConn = ENOTCONN,
  NotConnected = NotConn,

  NotSock = ENOTSOCK,
  NotSocket = NotSock,

  OpNotSupp = EOPNOTSUPP,
  OpNotSupported = OpNotSupp,
  OperationNotSupp = OpNotSupp,
  OperationNotSupported = OpNotSupp,
  NotSupported = OperationNotSupported,

  // The local end has been shut down on a connection oriented
  // socket.  In this case, the process will also receive a
  // SIGPIPE unless MSG_NOSIGNAL is set.
  Pipe = EPIPE,
};

void foo() {
  const auto send_flags = 0;
  const auto bytes_sent = send(s, bytes..., byte_count, send_flags);
  // VERIFY(bytes_sent != -1, "... {} ...", errno);
}

}
