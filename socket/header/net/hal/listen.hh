#pragma once

namespace flp::Net {

enum class ListenError {
  // Another socket is already listening on the same port.
 
  // (Internet domain sockets) The socket referred to by sockfd
  // had not previously been bound to an address and, upon
  // attempting to bind it to an ephemeral port, it was
  // determined that all port numbers in the ephemeral port
  // range are currently in use.  See the discussion of
  // /proc/sys/net/ipv4/ip_local_port_range in ip(7).
  AddrInUse = EADDRINUSE,
  AddressInUse = AddrInUse,

  // The argument sockfd is not a valid file descriptor.
  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
 
  // The file descriptor sockfd does not refer to a socket.
  NotSock = ENOTSOCK,
  NotSocket = NotSock,
 
  // The socket is not of a type that supports the listen() operation.
  OPNotSupp = EOPNOTSUPP,
  OPNotSupported = OPNotSupp,
  OperationNotSupported = OPNotSupported,
};

void foo() {
  const auto list_res = listen(s, 10);
  // VERIFY(list_res != -1, "... {} ...", errno);
}

}
