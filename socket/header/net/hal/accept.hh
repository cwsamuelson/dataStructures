#pragma once

namespace flp::Net {

enum class AcceptFlags {
  // Set the O_NONBLOCK file status flag on the open file
  // description (see open(2)) referred to by the new file
  // descriptor.  Using this flag saves extra calls to fcntl(2)
  // to achieve the same result.
  NonBlock = SOCK_NONBLOCK,
  NonBlocking = NonBlock,

  // Set the close-on-exec (FD_CLOEXEC) flag on the new file
  // descriptor.  See the description of the O_CLOEXEC flag in
  // open(2) for reasons why this may be useful.
  CLOEXEC = SOCK_CLOEXEC,
};

enum class AcceptError {
  // Error handling
  // Linux accept() (and accept4()) passes already-pending network
  // errors on the new socket as an error code from accept().  This
  // behavior differs from other BSD socket implementations.  For
  // reliable operation the application should detect the network
  // errors defined for the protocol after accept() and treat them like
  // EAGAIN by retrying.  In the case of TCP/IP, these are ENETDOWN,
  // EPROTO, ENOPROTOOPT, EHOSTDOWN, ENONET, EHOSTUNREACH, EOPNOTSUPP,
  // and ENETUNREACH.

  // The socket is marked nonblocking and no connections are
  // present to be accepted.  POSIX.1-2001 and POSIX.1-2008
  // allow either error to be returned for this case, and do not
  // require these constants to have the same value, so a
  // portable application should check for both possibilities.
  Again = EAGAIN,
  WouldBlock = EWOULDBLOCK,

  // sockfd is not an open file descriptor.
  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,

  // A connection has been aborted.
  ConnAborted = ECONNABORTED,

  // The addr argument is not in a writable part of the user
  // address space.
  Fault = EFAULT,

  // The system call was interrupted by a signal that was caught
  // before a valid connection arrived; see signal(7).
  Intr = EINTR,
  Interrupted = Intr,

  // Socket is not listening for connections, or addrlen is
  // invalid (e.g., is negative).

  // invalid value in flags.
  Inval = EINVAL,
  Invalid = Inval,

  // The per-process limit on the number of open file descriptors has been
  // reached.
  MFile = EMFILE,

  // The system-wide limit on the total number of open files has been reached.
  NFile = ENFILE,

  // Not enough free memory.  This often means that the memory
  // allocation is limited by the socket buffer limits, not by
  // the system memory.
  NoBufs = ENOBUFS,
  NoMem = ENOMEM,
  NoMemory = NoMem,

  // The file descriptor sockfd does not refer to a socket.
  NotSock = ENOTSOCK,

  // The referenced socket is not of type SOCK_STREAM.
  OpNotSupp = EOPNOTSUPP,
  OpNotSupported = OpNotSupp,
  OperationNotSupp = OpNotSupp,
  OperationNotSupported = OpNotSupp,

  // Firewall rules forbid connection.
  Perm = EPERM,

  // Protocol error.
  Proto = EPROTO,

  // In addition, network errors for the new socket and as defined for
  // the protocol may be returned.  Various Linux kernels can return
  // other errors such as ENOSR, ESOCKTNOSUPPORT, EPROTONOSUPPORT,
  // ETIMEDOUT.  The value ERESTARTSYS may be seen during a trace.

  ProtoNoSupport = EPROTONOSUPPORT,
  ProtocolNotSupported = ProtoNoSupport,
};

void foo() {
  const auto addr_size = sizeof(their_addr);
  const auto acc_res = accept(s, (sockaddr*)&client_addr, &addr_size);
  // VERIFY(acc_res != -1, "... {} ...", errno);
}

}
