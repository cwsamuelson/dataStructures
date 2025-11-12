#include <socket.hh>

#include <catch2/catch_all.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <memory>
#include <print>

using namespace flp;

struct ServerInfoDeleter {
  void operator()(addrinfo* info) {
    freeaddrinfo(info);
  }
};

TEST_CASE("`Sockets`::Client") {
  // reuse a socket to lose "Address already in use" errors.
  // Where to put it?  And look-up connotations.  Could a socket be picked up
  // and used as-is; is the previous connection still alive?

  // int yes = 1;
  // setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

  addrinfo hints{};
  addrinfo* info_ptr = nullptr;
  char ipstr[INET6_ADDRSTRLEN];

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  // VERIFY(getaddrinfo("www.google.com", "80", &hints, &info_ptr) == 0, "");
  if (const auto status = getaddrinfo("www.google.com", "80", &hints, &info_ptr); status != 0) {
    gai_strerror(status); // ???
    throw std::runtime_error("");
  }

  std::unique_ptr<addrinfo, ServerInfoDeleter> server_info(info_ptr);

  for (addrinfo* p = server_info.get(); p != nullptr; p = p-> ai_next) {
    void* addr = nullptr;
    const char* ipver = nullptr;
    sockaddr_in* ipv4 = nullptr;
    sockaddr_in6* ipv6 = nullptr;

    if (p->ai_family == AF_INET) {
      ipv4 = (sockaddr_in*)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else if (p->ai_family == AF_INET6) {
      ipv6 = (sockaddr_in6*)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    } else {
      throw std::runtime_error("");
    }

    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));

    std::println("\t{}: {}", ipver, ipstr);
  }

  auto s = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  // VERIFY(s != -1, "... {} ...", errno);

  // bind is optional for client
  auto bind_res = bind(s, server_info->ai_addr, server_info, ai_addrlen);
  // VERIFY(bind_res != -1, "... {} ...", errno);

  auto conn_res = connect(s, server_info->ai_addr, server_info->ai_addrlen);
  // VERIFY(conn_res != -1, "... {} ...", errno);

  CHECK(false);
}

TEST_CASE("`Sockets`::Server") {
  addrinfo hints{};
  addrinfo* info_ptr = nullptr;
  sockaddr_storage client_addr;

  // VERIFY(getaddrinfo("www.google.com", "80", &hints, &info_ptr) == 0, "");
  if (const auto status = getaddrinfo("www.google.com", "80", &hints, &info_ptr); status != 0) {
    gai_strerror(status); // ???
    throw std::runtime_error("");
  }

  auto s = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  // VERIFY(s != -1, "... {} ...", errno);

  auto bind_res = bind(s, server_info->ai_addr, server_info, ai_addrlen);
  // VERIFY(bind_res != -1, "... {} ...", errno);

  auto list_res = listen(s, 10);
  // VERIFY(list_res != -1, "... {} ...", errno);

  auto addr_size = sizeof(their_addr);
  auto acc_res = accept(s, (sockaddr*)&client_addr, &addr_size);
  // VERIFY(acc_res != -1, "... {} ...", errno);

  const auto conn_socket = acc_res;
}

TEST_CASE("`Sockets`::Server") {
  const auto socket = ...;

  const auto send_flags = 0;
  const auto bytes_sent = send(socket, bytes..., byte_count, send_flags);
  // VERIFY(bytes_sent != -1, "... {} ...", errno);

  const auto recv_flags = 0;
  const auto bytes_recvd = recv(socket, buffer..., buffer_size, recv_flags);
  // VERIFY(bytes_recvd != -1, "... {} ...", errno);
  // bytes_recvd may be 0 under the following conditions:
  // - stream socket closed by peer
  // - datagram socket sent 0-sized packet
  // - requested bytes to receive was 0
}

TEST_CASE("`Sockets`::Datagram") {
  const auto s = socket(...);

  const auto send_res = sendto(s, bytes..., byte_count, send_flags, sockaddr_in, sizeof(sockaddr(?)));
  // VERIFY(...);
  const auto recv_res = recvfrom(s, buffer..., buffer_size, recv_flags, sockaddr, ...);
  // VERIFY(...);
}

TEST_CASE("`Sockets`::Shutdown") {
  const auto s = socket(...);

  close(s);
  // or

  enum class How {
    DisallowReceive = 0,
    DisallowSends = 1,
    Close = 2,
  };

  shutdown(s, How::Close);
  // still need to close(s) to dispose of the file descriptor.
}

TEST_CASE("`Sockets`::Utilities") {
  sockaddr address{};

  const auto peer_res = getpeername(s, &address, sizeof(sockaddr));
  // VERIFY(peer_res != -1, "... {} ...", errno);
  // inet_ntop(), getnameinfo(), or gethostbyaddr()...

  const auto host_res = gethostname(s, &name_buf, buf_len);
  // VERIFY(host_res != -1, "... {} ...", errno);
}

TEST_CASE("`Sockets`::polling, blocking, and async") {
  // https://beej.us/guide/bgnet/html/split-wide/slightly-advanced-techniques.html#slightly-advanced-techniques

  // polling
  auto sock = socket(PF_INET, SOCK_STREAM, 0);
  fcntl(sock, F_SETFL, O_NONBLOCK);

  // select

  timeval tv;
  fd_set readfds;
  tv.tv_sec = 2;
  tv.tv_usec = 500'000;

  FD_ZERO(&readfds);
  FD_SET(STDIN, &readfds);

  select(STDIN + 1, &readfds, nullptr, nullptr, &tv);

  if (FD_ISSET(STDIN, &readfds)) {
    // key pressed!
  } else {
    // timeout
  }
}

enum class SendFlags {
  // Tell the link layer that forward progress happened: you got
  // a successful reply from the other side.  If the link layer
  // doesn't get this it will regularly reprobe the neighbor
  // (e.g., via a unicast ARP).  Valid only on SOCK_DGRAM and
  // SOCK_RAW sockets and currently implemented only for IPv4
  // and IPv6.  See arp(7) for details.
  MSG_CONFIRM,
 
  // Don't use a gateway to send out the packet, send to hosts
  // only on directly connected networks.  This is usually used
  // only by diagnostic or routing programs.  This is defined
  // only for protocol families that route; packet sockets
  // don't.
  MSG_DONTROUTE,
 
  // Enables nonblocking operation; if the operation would
  // block, EAGAIN or EWOULDBLOCK is returned.  This provides
  // similar behavior to setting the O_NONBLOCK flag (via the
  // fcntl(2) F_SETFL operation), but differs in that
  // MSG_DONTWAIT is a per-call option, whereas O_NONBLOCK is a
  // setting on the open file description (see open(2)), which
  // will affect all threads in the calling process as well as
  // other processes that hold file descriptors referring to the
  // same open file description.
  MSG_DONTWAIT,
 
  // Terminates a record (when this notion is supported, as for
  // sockets of type SOCK_SEQPACKET).
  MSG_EOR,
 
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
  MSG_MORE,
 
  // Don't generate a SIGPIPE signal if the peer on a stream-
  // oriented socket has closed the connection.  The EPIPE error
  // is still returned.  This provides similar behavior to using
  // sigaction(2) to ignore SIGPIPE, but, whereas MSG_NOSIGNAL
  // is a per-call feature, ignoring SIGPIPE sets a process
  // attribute that affects all threads in the process.
  MSG_NOSIGNAL,
 
  // Sends out-of-band data on sockets that support this notion
  // (e.g., of type SOCK_STREAM); the underlying protocol must
  // also support out-of-band data.
  MSG_OOB,
 
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
  MSG_FASTOPEN,
};

enum class SendErrors {
  // Write permission is denied on the destination socket file,
  // or search permission is denied for one of the directories
  // the path prefix.  (See path_resolution(7).)
 
  // (For UDP sockets) An attempt was made to send to a
  // network/broadcast address as though it was a unicast
  // address.
  EACCES, // (For UNIX domain sockets, which are identified by pathname)
 
  // The socket is marked nonblocking and the requested
  // operation would block.  POSIX.1-2001 allows either error to
  // be returned for this case, and does not require these
  // constants to have the same value, so a portable application
  // should check for both possibilities.
  EWOULDBLOCK, // or EAGAIN
 
  // The socket referred to
  // by sockfd had not previously been bound to an address and,
  // upon attempting to bind it to an ephemeral port, it was
  // determined that all port numbers in the ephemeral port
  // range are currently in use.  See the discussion of
  // /proc/sys/net/ipv4/ip_local_port_range in ip(7).
  EAGAIN, // (Internet domain datagram sockets)
 
  // Another Fast Open is in progress.
  EALREADY,

  // sockfd is not a valid open file descriptor.
  EBADF,
 
  // Connection reset by peer.
  ECONNRESET,
 
  // The socket is not connection-mode, and no peer address is set.
  EDESTADDRREQ,
 
  // An invalid user space address was specified for an argument.
  EFAULT,

  // A signal occurred before any data was transmitted; see signal(7).
  EINTR,

  // Invalid argument passed.
  EINVAL,
 
  // The connection-mode socket was connected already but a
  // recipient was specified.  (Now either this error is
  // returned, or the recipient specification is ignored.)
  EISCONN,
 
  // The socket type requires that message be sent atomically,
  // and the size of the message to be sent made this
  // impossible.
  EMSGSIZE,
 
  // The output queue for a network interface was full.  This
  // generally indicates that the interface has stopped sending,
  // but may be caused by transient congestion.  (Normally, this
  // does not occur in Linux.  Packets are just silently dropped
  // when a device queue overflows.)
  ENOBUFS,

  // No memory available.
  ENOMEM,
 
  // The socket is not connected, and no target has been given.
  ENOTCONN,
 
  // The file descriptor sockfd does not refer to a socket.
  ENOTSOCK,
 
  // Some bit in the flags argument is inappropriate for the
  // socket type.
  EOPNOTSUPP,
 
  // The local end has been shut down on a connection oriented
  // socket.  In this case, the process will also receive a
  // SIGPIPE unless MSG_NOSIGNAL is set.
  EPIPE,
};

enum class RecvFlags {
  // Set the close-on-exec flag for the file descriptor received
  // via a UNIX domain file descriptor using the SCM_RIGHTS
  // operation (described in unix(7)).  This flag is useful for
  // the same reasons as the O_CLOEXEC flag of open(2).
  MSG_CMSG_CLOEXEC, // recvmsg() only

  // Enables nonblocking operation; if the operation would
  // block, the call fails with the error EAGAIN or EWOULDBLOCK.
  // This provides similar behavior to setting the O_NONBLOCK
  // flag (via the fcntl(2) F_SETFL operation), but differs in
  // that MSG_DONTWAIT is a per-call option, whereas O_NONBLOCK
  // is a setting on the open file description (see open(2)),
  // which will affect all threads in the calling process as
  // well as other processes that hold file descriptors
  // referring to the same open file description.
  MSG_DONTWAIT,
 
  // This flag specifies that queued errors should be received
  // from the socket error queue.  The error is passed in an
  // ancillary message with a type dependent on the protocol
  // (for IPv4 IP_RECVERR).  The user should supply a buffer of
  // sufficient size.  See cmsg(3) and ip(7) for more
  // information.  The payload of the original packet that
  // caused the error is passed as normal data via msg_iovec.
  // The original destination address of the datagram that
  // caused the error is supplied via msg_name.
 
  // The error is supplied in a sock_extended_err structure:
 
  //     #define SO_EE_ORIGIN_NONE    0
  //     #define SO_EE_ORIGIN_LOCAL   1
  //     #define SO_EE_ORIGIN_ICMP    2
  //     #define SO_EE_ORIGIN_ICMP6   3
 
  //     struct sock_extended_err
  //     {
  //         uint32_t ee_errno;   /* Error number */
  //         uint8_t  ee_origin;  /* Where the error originated */
  //         uint8_t  ee_type;    /* Type */
  //         uint8_t  ee_code;    /* Code */
  //         uint8_t  ee_pad;     /* Padding */
  //         uint32_t ee_info;    /* Additional information */
  //         uint32_t ee_data;    /* Other data */
  //         /* More data may follow */
  //     };
 
  //     struct sockaddr *SO_EE_OFFENDER(struct sock_extended_err *);
 
  // ee_errno contains the errno number of the queued error.
  // ee_origin is the origin code of where the error originated.
  // The other fields are protocol-specific.  The macro
  // SO_EE_OFFENDER returns a pointer to the address of the
  // network object where the error originated from given a
  // pointer to the ancillary message.  If this address is not
  // known, the sa_family member of the sockaddr contains
  // AF_UNSPEC and the other fields of the sockaddr are
  // undefined.  The payload of the packet that caused the error
  // is passed as normal data.
 
  // For local errors, no address is passed (this can be checked
  // with the cmsg_len member of the cmsghdr).  For error
  // receives, the MSG_ERRQUEUE flag is set in the msghdr.
  // After an error has been passed, the pending socket error is
  // regenerated based on the next queued error and will be
  // passed on the next socket operation.
  MSG_ERRQUEUE,
 
  // This flag requests receipt of out-of-band data that would
  // not be received in the normal data stream.  Some protocols
  // place expedited data at the head of the normal data queue,
  // and thus this flag cannot be used with such protocols.
  MSG_OOB,
 
  // This flag causes the receive operation to return data from
  // the beginning of the receive queue without removing that
  // data from the queue.  Thus, a subsequent receive call will
  // return the same data.
  MSG_PEEK,
 
  // For raw (AF_PACKET), Internet datagram (since Linux
  // 2.4.27/2.6.8), netlink (since Linux 2.6.22), and UNIX
  // datagram as well as sequenced-packet (since Linux 3.4)
  // sockets: return the real size of the packet or datagram,
  // even when it was longer than the passed buffer.
 
  // For use with Internet stream sockets, see tcp(7).
  MSG_TRUNC,
 
  // This flag requests that the operation block until the full
  // request is satisfied.  However, the call may still return
  // less data than requested if a signal is caught, an error or
  // disconnect occurs, or the next data to be received is of a
  // different type than that returned.  This flag has no effect
  // for datagram sockets.
  MSG_WAITALL,
};

enum class RecvErrors {
  // The socket is marked nonblocking and the receive operation
  // would block, or a receive timeout had been set and the
  // timeout expired before data was received.  POSIX.1 allows
  // either error to be returned for this case, and does not
  // require these constants to have the same value, so a
  // portable application should check for both possibilities.
  EAGAIN, EWOULDBLOCK,

  // The argument sockfd is an invalid file descriptor.
  EBADF,
 
  // A remote host refused to allow the network connection
  // (typically because it is not running the requested
  // service).
  ECONNREFUSED,
 
  // The receive buffer pointer(s) point outside the process's
  // address space.
  EFAULT,
 
  // The receive was interrupted by delivery of a signal before
  // any data was available; see signal(7).
  EINTR,

  // Invalid argument passed.
  EINVAL,

  // Could not allocate memory for recvmsg().
  ENOMEM,
 
  // The socket is associated with a connection-oriented
  // protocol and has not been connected (see connect(2) and
  // accept(2)).
  ENOTCONN,
 
  // The file descriptor sockfd does not refer to a socket.
  ENOTSOCK
};
