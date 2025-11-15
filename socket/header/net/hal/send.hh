#pragma once

namespace flp::Net {

enum class SendFlags {
  // Tell the link layer that forward progress happened: you got
  // a successful reply from the other side.  If the link layer
  // doesn't get this it will regularly reprobe the neighbor
  // (e.g., via a unicast ARP).  Valid only on SOCK_DGRAM and
  // SOCK_RAW sockets and currently implemented only for IPv4
  // and IPv6.  See arp(7) for details.
  Confirm = MSG_CONFIRM,

  // Don't use a gateway to send out the packet, send to hosts
  // only on directly connected networks.  This is usually used
  // only by diagnostic or routing programs.  This is defined
  // only for protocol families that route; packet sockets
  // don't.
  DontRoute = MSG_DONTROUTE,

  // Enables nonblocking operation; if the operation would
  // block, EAGAIN or EWOULDBLOCK is returned.  This provides
  // similar behavior to setting the O_NONBLOCK flag (via the
  // fcntl(2) F_SETFL operation), but differs in that
  // MSG_DONTWAIT is a per-call option, whereas O_NONBLOCK is a
  // setting on the open file description (see open(2)), which
  // will affect all threads in the calling process as well as
  // other processes that hold file descriptors referring to the
  // same open file description.
  DontWait = MSG_DONTWAIT,

  // Terminates a record (when this notion is supported, as for
  // sockets of type SOCK_SEQPACKET).
  EndOfRecord = MSG_EOR,

  // The caller has more data to send.  This flag is used with
  // TCP sockets to obtain the same effect as the TCP_CORK
  // socket option (see tcp(7)), with the difference that this
  // flag can be set on a per-call basis.

  // Since Linux 2.6, this flag is also supported for UDP
  // sockets, and informs the kernel to package all of the data
  // sent in calls with this flag set into a single datagram
  // which is transmitted only when a call is performed that
  // does not specify this flag.  (See also the UDP_CORK socket
  // option described in udp(7).)
  More = MSG_MORE,

  // Don't generate a SIGPIPE signal if the peer on a stream-
  // oriented socket has closed the connection.  The EPIPE error
  // is still returned.  This provides similar behavior to using
  // sigaction(2) to ignore SIGPIPE, but, whereas MSG_NOSIGNAL
  // is a per-call feature, ignoring SIGPIPE sets a process
  // attribute that affects all threads in the process.
  NoSignal = MSG_NOSIGNAL,

  // Sends out-of-band data on sockets that support this notion
  // (e.g., of type SOCK_STREAM); the underlying protocol must
  // also support out-of-band data.
  OutOfBand = MSG_OOB,
  OOB = OutOfBand,

  // Attempts TCP Fast Open (RFC7413) and sends data in the SYN
  // like a combination of connect(2) and write(2), by
  // performing an implicit connect(2) operation.  It blocks
  // until the data is buffered and the handshake has completed.
  // For a non-blocking socket, it returns the number of bytes
  // buffered and sent in the SYN packet.  If the cookie is not
  // available locally, it returns EINPROGRESS, and sends a SYN
  // with a Fast Open cookie request automatically.  The caller
  // needs to write the data again when the socket is connected.
  // On errors, it sets the same errno as connect(2) if the
  // handshake fails.  This flag requires enabling TCP Fast Open
  // client support on sysctl net.ipv4.tcp_fastopen.

  // Refer to TCP_FASTOPEN_CONNECT socket option in tcp(7) for
  // an alternative approach.
  FastOpen = MSG_FASTOPEN,
};

enum class SendErrors {
  // Write permission is denied on the destination socket file,
  // or search permission is denied for one of the directories
  // the path prefix.  (See path_resolution(7).)

  // (For UDP sockets) An attempt was made to send to a
  // network/broadcast address as though it was a unicast
  // address.
  Access = EACCES, // (For UNIX domain sockets, which are identified by pathname)

  // The socket is marked nonblocking and the requested
  // operation would block.  POSIX.1-2001 allows either error to
  // be returned for this case, and does not require these
  // constants to have the same value, so a portable application
  // should check for both possibilities.
  WouldBlock = EWOULDBLOCK, // or EAGAIN

  // The socket referred to
  // by sockfd had not previously been bound to an address and,
  // upon attempting to bind it to an ephemeral port, it was
  // determined that all port numbers in the ephemeral port
  // range are currently in use.  See the discussion of
  // /proc/sys/net/ipv4/ip_local_port_range in ip(7).
  Again = EAGAIN, // (Internet domain datagram sockets)

  // Another Fast Open is in progress.
  Already = EALREADY,

  // sockfd is not a valid open file descriptor.
  BadFileDescriptor = EBADF,
  BadFD = BadFileDescriptor,

  // Connection reset by peer.
  ConnectionReset = ECONNRESET,
  Reset = ConnectionReset,

  // The socket is not connection-mode, and no peer address is set.
  DestinationAddressRequest = EDESTADDRREQ, // ???

  // An invalid user space address was specified for an argument.
  Fault = EFAULT,

  // A signal occurred before any data was transmitted; see signal(7).
  Interrupted = EINTR,

  // Invalid argument passed.
  Invalid = EINVAL,
  InvalidArgument = Invalid,

  // The connection-mode socket was connected already but a
  // recipient was specified.  (Now either this error is
  // returned, or the recipient specification is ignored.)
  IsConnected = EISCONN,

  // The socket type requires that message be sent atomically,
  // and the size of the message to be sent made this
  // impossible.
  MessageSize = EMSGSIZE,

  // The output queue for a network interface was full.  This
  // generally indicates that the interface has stopped sending,
  // but may be caused by transient congestion.  (Normally, this
  // does not occur in Linux.  Packets are just silently dropped
  // when a device queue overflows.)
  NoBuffers = ENOBUFS,

  // No memory available.
  NoMemory = ENOMEM,

  // The socket is not connected, and no target has been given.
  NotConnected = ENOTCONN,

  // The file descriptor sockfd does not refer to a socket.
  NotSocket = ENOTSOCK,

  // Some bit in the flags argument is inappropriate for the
  // socket type.
  OperationNotSupported = EOPNOTSUPP,
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
