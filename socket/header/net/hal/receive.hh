#pragma once

namespace flp::Net {

enum class RecvErrors {
  // The socket is marked nonblocking and the receive operation
  // would block, or a receive timeout had been set and the
  // timeout expired before data was received.  POSIX.1 allows
  // either error to be returned for this case, and does not
  // require these constants to have the same value, so a
  // portable application should check for both possibilities.
  Again = EAGAIN,
  WouldBlock = EWOULDBLOCK,

  // The argument sockfd is an invalid file descriptor.
  BadFileDescriptor = EBADF,
  BadFD = BadFileDescriptor,

  // A remote host refused to allow the network connection
  // (typically because it is not running the requested
  // service).
  ConnectionRefused = ECONNREFUSED,

  // The receive buffer pointer(s) point outside the process's
  // address space.
  Fault = EFAULT,

  // The receive was interrupted by delivery of a signal before
  // any data was available; see signal(7).
  Interrupted = EINTR,

  // Invalid argument passed.
  Invalid = EINVAL,
  InvalidArgument = Invalid,

  // Could not allocate memory for recvmsg().
  NoMemory = ENOMEM,

  // The socket is associated with a connection-oriented
  // protocol and has not been connected (see connect(2) and
  // accept(2)).
  NotConnected = ENOTCONN,

  // The file descriptor sockfd does not refer to a socket.
  NotSocket = ENOTSOCK,
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
