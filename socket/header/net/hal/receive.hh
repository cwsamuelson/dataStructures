#pragma once

namespace flp::Net {

enum class RecvErrors {
  Again = EAGAIN,
  WouldBlock = EWOULDBLOCK,

  BadF = EBADF,
  BadFD = BadF,
  BadFileDescriptor = BadFD,

  ConnRefused = ECONNREFUSED,
  ConnectionRefused = ConnRefused,

  Fault = EFAULT,

  Intr = EINTR,
  Interrupted = Intr,

  Invalid = EINVAL,
  InvalidArgument = Invalid,

  NoMem = ENOMEM,
  NoMemory = NoMem,

  NotConn = ENOTCONN,
  NotConnected = NotConn,

  NotSock = ENOTSOCK,
  NotSocket = NotSock,
};

void foo() {
  const auto recv_flags = 0;
  const auto bytes_recvd = recv(s, buffer..., buffer_size, recv_flags);
  // VERIFY(bytes_recvd != -1, "... {} ...", errno);

  // bytes_recvd may be 0 under the following conditions:
  // - stream socket closed by peer
  // - datagram socket sent 0-sized packet
  // - requested bytes to receive was 0
}

}
