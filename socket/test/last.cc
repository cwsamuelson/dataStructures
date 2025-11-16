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

// getaddrinfo
namespace AddressInfo {

struct ServerInfoDeleter {
  void operator()(addrinfo* info) {
    freeaddrinfo(info);
  }
};

enum class Family {
  Inet = AF_INET,
  Inet6 = AF_INET6,
  Unspec = AF_UNSPEC,

  Internet = Inet,
  Internet6 = Inet6,
  Unspecified = Unspec,

  IPV4 = Internet,
  IPV6 = Internet6,
  Any = Unspecified,
};

enum class SocketType {
  Stream = SOCK_STREAM,
  Dgram = SOCK_DGRAM,
  Unspecified = 0,

  Datagram = Dgram,
  Any = Unspecified,
};

enum class Protocol {
  Any = 0,
  Unspecified = Any,
};

enum class Flags {
  Passive = AI_PASSIVE,

  NumericServ = AI_NUMERICSERV,
  NumericService = NumericServ,

  CanonName = AI_CANONNAME,
  CanonicalName = CanonName,

  AddrConfig = AI_ADDRCONFIG,
  AddressConfig = AddrConfig,

  V4Mapped = AI_V4MAPPED,

  All = AI_ALL,

  // Extensions

  // If this flag is specified, then the node name given in node
  // is converted to IDN format if necessary.  The source
  // encoding is that of the current locale.

  // If the input name contains non-ASCII characters, then the
  // IDN encoding is used.  Those parts of the node name
  // (delimited by dots) that contain non-ASCII characters are
  // encoded using ASCII Compatible Encoding (ACE) before being
  // passed to the name resolution functions.
  IDN = AI_IDN,

  // After a successful name lookup, and if the AI_CANONNAME
  // flag was specified, getaddrinfo() will return the canonical
  // name of the node corresponding to the addrinfo structure
  // value passed back.  The return value is an exact copy of
  // the value returned by the name resolution function.

  // If the name is encoded using ACE, then it will contain the
  // xn-- prefix for one or more components of the name.  To
  // convert these components into a readable form the
  // AI_CANONIDN flag can be passed in addition to AI_CANONNAME.
  // The resulting string is encoded using the current locale's
  // encoding.
  CanonIDN = AI_CANONIDN,

  // Setting these flags will enable the IDNA_ALLOW_UNASSIGNED
  // (allow unassigned Unicode code points) and
  // IDNA_USE_STD3_ASCII_RULES (check output to make sure it is
  // a STD3 conforming hostname) flags respectively to be used
  // in the IDNA handling.
  IDNAAllowUnassigned = AI_IDN_ALLOW_UNASSIGNED,
  IDNAUseSTD3ASCIIRules = AI_IDN_USE_STD3_ASCII_RULES,
};

enum class Error {
  Success = 0,

  // The specified network host does not have any network
  // addresses in the requested address family.
  AddrFamily = EAI_ADDRFAMILY,
  AddressFamily = AddrFamily,

  // The name server returned a temporary failure indication.
  // Try again later.
  Again = EAI_AGAIN,
  TryAgain = Again,
  TryLater = TryAgain,

  // hints.ai_flags contains invalid flags; or, hints.ai_flags
  // included AI_CANONNAME and node was NULL.
  BadFlags = EAI_BADFLAGS,

  // The name server returned a permanent failure indication.
  Fail = EAI_FAIL,

  // The requested address family is not supported.
  Family = EAI_FAMILY,
  InvalidFamily = Family,
  UnsupportedFamily = InvalidFamily,

  // Out of memory.
  Memory = EAI_MEMORY,
  OutOfMemory = Memory,
  OOM = OutOfMemory,

  // The specified network host exists, but does not have any
  // network addresses defined.
  NoData = EAI_NODATA,

  // The node or service is not known; or both node and service
  // are NULL; or AI_NUMERICSERV was specified in hints.ai_flags
  // and service was not a numeric port-number string.
  NoName = EAI_NONAME,

  // The requested service is not available for the requested
  // socket type.  It may be available through another socket
  // type.  For example, this error could occur if service was
  // "shell" (a service available only on stream sockets), and
  // either hints.ai_protocol was IPPROTO_UDP, or
  // hints.ai_socktype was SOCK_DGRAM; or the error could occur
  // if service was not NULL, and hints.ai_socktype was SOCK_RAW
  // (a socket type that does not support the concept of
  // services).
  Service = EAI_SERVICE,

  // The requested socket type is not supported.  This could
  // occur, for example, if hints.ai_socktype and
  // hints.ai_protocol are inconsistent (e.g., SOCK_DGRAM and
  // IPPROTO_TCP, respectively).
  SockType = EAI_SOCKTYPE,

  // Other system error; errno is set to indicate the error.
  System = EAI_SYSTEM,
  CheckErroNo = System,
  CheckErroNumber = CheckErroNo,
};

}

// socket(...)
namespace Socket {

enum class Family {
  Inet = AF_INET,
  Inet6 = AF_INET6,

  Internet = Inet,
  Internet6 = Inet6,

  IPV4 = Internet,
  IPV6 = Internet6,

  UNIX = AF_UNIX,
  Local = AF_LOCAL,
  AX25 = AF_AX25,
  IPX = AF_IPX,
  AppleTalk = AF_APPLETALK,
  X25 = AF_X25,
  ISO8208 = X25,
  DECnet = AF_DECnet,
  Key = AF_KEY,
  NetLink = AF_NETLINK,
  Packet = AF_PACKET,
  RDS = AF_RDS,
  PPPOX = AF_PPPOX,
  LLC = AF_LLC,
  IB = AF_IB,
  InfiniBand = IB,
  MPLS = AF_MPLS,
  MultiProtocolLabelSwitching = MPLS,
  CAN = AF_CAN,
  ControllerAreaNetwork = CAN,
  TIPC = AF_TIPC,
  ClusterDomainSockets = TIPC,
  BlueTooth = AF_BLUETOOTH,
  ALG = AF_ALG,
  VSock = AF_VSOCK,
  VSocket = VSock,
  VMSocket = VSocket,
  KCM = AF_KCM,
  KernelConnectionMultiplexer = KCM,
  XDP = AF_XDP,
  ExpressDataPath = XDP,
};

enum class Type {
  // Provides sequenced, reliable, two-way, connection-based
  // byte streams.  An out-of-band data transmission mechanism
  // may be supported.
  Stream = SOCK_STREAM,

  // Supports datagrams (connectionless, unreliable messages of
  // a fixed maximum length).
  Dgram = SOCK_DGRAM,
  Datagram = Dgram,

  // Provides a sequenced, reliable, two-way connection-based
  // data transmission path for datagrams of fixed maximum
  // length; a consumer is required to read an entire packet
  // with each input system call.
  SeqPacket = SOCK_SEQPACKET,
  SequencedPacket = SeqPacket,

  // Provides raw network protocol access.
  Raw = SOCK_RAW,

  // Provides a reliable datagram layer that does not guarantee ordering.
  RDM = SOCK_RDM,

  // Obsolete and should not be used in new programs; see packet(7).
  Packet = SOCK_PACKET,
};

enum class Type2 {
  // Set the O_NONBLOCK file status flag on the open file
  // description (see open(2)) referred to by the new file
  // descriptor.  Using this flag saves extra calls to fcntl(2)
  // to achieve the same result.
  NonBlock = SOCK_NONBLOCK,
  NonBlocking,

  // Set the close-on-exec (FD_CLOEXEC) flag on the new file
  // descriptor.  See the description of the O_CLOEXEC flag in
  // open(2) for reasons why this may be useful.
  CLOEXEC = SOCK_CLOEXEC,
};

enum class Error {
  // Permission to create a socket of the specified type and/or
  // protocol is denied.
  Acces = EACCES,
  NoPermission = Access,

  // The implementation does not support the specified address
  // family.
  AFNoSupport = EAFNOSUPPORT,
  FamNoSupport = AFNoSupport,
  FamilyNoSupport = FamNoSupport,
  FamilyNotSupported = FamilyNoSupport,

  // Unknown protocol, protocol family not available, or invalid flags in type.
  Inval = EINVAL,
  Invalid = Inval,

  // The per-process limit on the number of open file
  // descriptors has been reached.
  MFile = EMFILE,

  // The system-wide limit on the total number of open files has
  // been reached.
  NFile = ENFILE,

  // Insufficient memory is available.  The socket cannot be
  // created until sufficient resources are freed.
  NoBufs = ENOBUFS,
  NoMem = ENOMEM,
  NoMemory = NoMem,

  // The protocol type or the specified protocol is not
  // supported within this domain.
  ProtoNoSupport = EPROTONOSUPPORT,
  ProtocolNotSupported = ProtoNoSupport,
};

// https://www.man7.org/linux/man-pages/man7/socket.7.html
// setsockopt
enum class Options {
  // Returns a value indicating whether or not this socket has
  // been marked to accept connections with listen(2).  The
  // value 0 indicates that this is not a listening socket, the
  // value 1 indicates that this is a listening socket.  This
  // socket option is read-only.
  AcceptConn = SO_ACCEPTCONN,
  AcceptConnection = AcceptConn,

  // Attach a classic BPF (SO_ATTACH_FILTER) or an extended BPF
  // (SO_ATTACH_BPF) program to the socket for use as a filter
  // of incoming packets.  A packet will be dropped if the
  // filter program returns zero.  If the filter program returns
  // a nonzero value which is less than the packet's data size,
  // the packet will be truncated to the size returned.  If the
  // value returned by the filter is greater than or equal to
  // the packet's data size, the packet is allowed to proceed
  // unmodified.

  // The argument for SO_ATTACH_FILTER is a sock_fprog
  // structure, defined in <linux/filter.h>:

  //     struct sock_fprog {
  //         unsigned short      len;
  //         struct sock_filter *filter;
  //     };

  // The argument for SO_ATTACH_BPF is a file descriptor
  // returned by the bpf(2) system call and must refer to a
  // program of type BPF_PROG_TYPE_SOCKET_FILTER.

  // These options may be set multiple times for a given socket,
  // each time replacing the previous filter program.  The
  // classic and extended versions may be called on the same
  // socket, but the previous filter will always be replaced
  // such that a socket never has more than one filter defined.

  // Both classic and extended BPF are explained in the kernel
  // source file Documentation/networking/filter.txt
  AttachFilter = SO_ATTACH_FILTER,
  AttachBPF = SO_ATTACH_BPF,

  // For use with the SO_REUSEPORT option, these options allow
  // the user to set a classic BPF (SO_ATTACH_REUSEPORT_CBPF) or
  // an extended BPF (SO_ATTACH_REUSEPORT_EBPF) program which
  // defines how packets are assigned to the sockets in the
  // reuseport group (that is, all sockets which have

  // SO_REUSEPORT set and are using the same local address to
  // receive packets).

  // The BPF program must return an index between 0 and N-1
  // representing the socket which should receive the packet
  // (where N is the number of sockets in the group).  If the
  // BPF program returns an invalid index, socket selection will
  // fall back to the plain SO_REUSEPORT mechanism.

  // Sockets are numbered in the order in which they are added
  // to the group (that is, the order of bind(2) calls for UDP
  // sockets or the order of listen(2) calls for TCP sockets).
  // New sockets added to a reuseport group will inherit the BPF
  // program.  When a socket is removed from a reuseport group
  // (via close(2)), the last socket in the group will be moved
  // into the closed socket's position.

  // These options may be set repeatedly at any time on any
  // socket in the group to replace the current BPF program used
  // by all sockets in the group.

  // SO_ATTACH_REUSEPORT_CBPF takes the same argument type as
  // SO_ATTACH_FILTER and SO_ATTACH_REUSEPORT_EBPF takes the
  // same argument type as SO_ATTACH_BPF.

  // UDP support for this feature is available since Linux 4.5;
  // TCP support is available since Linux 4.6.
  AttachReusePortCBPF = SO_ATTACH_REUSEPORT_CBPF,
  AttachReusePortEBPF = SO_ATTACH_REUSEPORT_EBPF,

  // Bind this socket to a particular device like “eth0”, as
  // specified in the passed interface name.  If the name is an
  // empty string or the option size is zero, the socket device
  // binding is removed.  The passed option is a variable-size
  // null-terminated interface name string with the maximum size
  // of IFNAMSIZ.  If a socket is bound to an interface, only
  // packets received from that particular interface are
  // processed by the socket.  Note that this works only for
  // some socket types, particularly AF_INET sockets.  It is not
  // supported for packet sockets (use normal bind(2) there).

  // Before Linux 3.8, this socket option could be set, but
  // could not retrieved with getsockopt(2).  Since Linux 3.8,
  // it is readable.  The optlen argument should contain the
  // buffer size available to receive the device name and is
  // recommended to be IFNAMSIZ bytes.  The real device name
  // length is reported back in the optlen argument.
  BindToDevice = SO_BINDTODEVICE,

  // Set or get the broadcast flag.  When enabled, datagram
  // sockets are allowed to send packets to a broadcast address.
  // This option has no effect on stream-oriented sockets.
  Broadcast = SO_BROADCAST,

  // Enable BSD bug-to-bug compatibility.  This is used by the
  // UDP protocol module in Linux 2.0 and 2.2.  If enabled, ICMP
  // errors received for a UDP socket will not be passed to the
  // user program.  In later kernel versions, support for this
  // option has been phased out: Linux 2.4 silently ignores it,
  // and Linux 2.6 generates a kernel warning (printk()) if a
  // program uses this option.  Linux 2.0 also enabled BSD bug-
  // to-bug compatibility options (random header changing,
  // skipping of the broadcast flag) for raw sockets with this
  // option, but that was removed in Linux 2.2.
  BSDCompat = SO_BSDCOMPAT,

  // Enable socket debugging.  Allowed only for processes with
  // the CAP_NET_ADMIN capability or an effective user ID of 0.
  Debug = SO_DEBUG,

  // These two options, which are synonyms, may be used to
  // remove the classic or extended BPF program attached to a
  // socket with either SO_ATTACH_FILTER or SO_ATTACH_BPF.  The
  // option value is ignored.
  DetachFilter = SO_DETACH_FILTER,
  DetachBPF = SO_DETACH_BPF,

  // Retrieves the socket domain as an integer, returning a
  // value such as AF_INET6.  See socket(2) for details.  This
  // socket option is read-only.
  Domain = SO_DOMAIN,

  // Get and clear the pending socket error.  This socket option
  // is read-only.  Expects an integer.
  Error = SO_ERROR,

  // Don't send via a gateway, send only to directly connected
  // hosts.  The same effect can be achieved by setting the
  // MSG_DONTROUTE flag on a socket send(2) operation.  Expects
  // an integer boolean flag.
  DontRoute = SO_DONTROUTE,

  // Sets or gets the CPU affinity of a socket.  Expects an
  // integer flag.

  //     int cpu = 1;
  //     setsockopt(fd, SOL_SOCKET, SO_INCOMING_CPU, &cpu,
  //                sizeof(cpu));

  // Because all of the packets for a single stream (i.e., all
  // packets for the same 4-tuple) arrive on the single RX queue
  // that is associated with a particular CPU, the typical use
  // case is to employ one listening process per RX queue, with
  // the incoming flow being handled by a listener on the same
  // CPU that is handling the RX queue.  This provides optimal
  // NUMA behavior and keeps CPU caches hot.
  IncomingCPU = SO_INCOMING_CPU,

  // Returns a system-level unique ID called NAPI ID that is
  // associated with a RX queue on which the last packet
  // associated with that socket is received.

  // This can be used by an application to split the incoming
  // flows among worker threads based on the RX queue on which
  // the packets associated with the flows are received.  It
  // allows each worker thread to be associated with a NIC HW
  // receive queue and service all the connection requests
  // received on that RX queue.  This mapping between an app
  // thread and a HW NIC queue streamlines the flow of data from
  // the NIC to the application.
  IncomingNAPIID = SO_INCOMING_NAPI_ID,

  // Enable sending of keep-alive messages on connection-
  // oriented sockets.  Expects an integer boolean flag.
  KeepAlive = SO_KEEPALIVE,

  // Sets or gets the SO_LINGER option.  The argument is a
  // linger structure.

  //     struct linger {
  //         int l_onoff;    /* linger active */
  //         int l_linger;   /* how many seconds to linger for */
  //     };

  // When enabled, a close(2) or shutdown(2) will not return
  // until all queued messages for the socket have been
  // successfully sent or the linger timeout has been reached.
  // Otherwise, the call returns immediately and the closing is
  // done in the background.  When the socket is closed as part
  // of exit(2), it always lingers in the background.
  Linger = SO_LINGER,

  // When set, this option will prevent changing the filters
  // associated with the socket.  These filters include any set
  // using the socket options SO_ATTACH_FILTER, SO_ATTACH_BPF,
  // SO_ATTACH_REUSEPORT_CBPF, and SO_ATTACH_REUSEPORT_EBPF.

  // The typical use case is for a privileged process to set up
  // a raw socket (an operation that requires the CAP_NET_RAW
  // capability), apply a restrictive filter, set the
  // SO_LOCK_FILTER option, and then either drop its privileges
  // or pass the socket file descriptor to an unprivileged
  // process via a UNIX domain socket.

  // Once the SO_LOCK_FILTER option has been enabled, attempts
  // to change or remove the filter attached to a socket, or to
  // disable the SO_LOCK_FILTER option will fail with the error
  // EPERM.
  LockFilter = SO_LOCK_FILTER,

  // Set the mark for each packet sent through this socket
  // (similar to the netfilter MARK target but socket-based).
  // Changing the mark can be used for mark-based routing
  // without netfilter or for packet filtering.  Setting this
  // option requires the CAP_NET_ADMIN or CAP_NET_RAW (since
  // Linux 5.17) capability.
  Mark = SO_MARK,

  // If this option is enabled, out-of-band data is directly
  // placed into the receive data stream.  Otherwise, out-of-
  // band data is passed only when the MSG_OOB flag is set
  // during receiving.
  OOBINLINE = SO_OOBINLINE,

  // Enable or disable the receiving of the SCM_CREDENTIALS
  // control message.  For more information, see unix(7).
  PassCred = SO_PASSCRED,
  PassCredentials = PassCred,

  // Enable or disable the receiving of the SCM_SECURITY control
  // message.  For more information, see unix(7).
  PassSec = SO_PASSSEC,
  PassSecurity = PassSec,

  // This option, which is currently supported only for unix(7)
  // sockets, sets the value of the "peek offset" for the
  // recv(2) system call when used with MSG_PEEK flag.

  // When this option is set to a negative value (it is set to
  // -1 for all new sockets), traditional behavior is provided:
  // recv(2) with the MSG_PEEK flag will peek data from the
  // front of the queue.

  // When the option is set to a value greater than or equal to
  // zero, then the next peek at data queued in the socket will
  // occur at the byte offset specified by the option value.  At
  // the same time, the "peek offset" will be incremented by the
  // number of bytes that were peeked from the queue, so that a
  // subsequent peek will return the next data in the queue.

  // If data is removed from the front of the queue via a call
  // to recv(2) (or similar) without the MSG_PEEK flag, the
  // "peek offset" will be decreased by the number of bytes
  // removed.  In other words, receiving data without the
  // MSG_PEEK flag will cause the "peek offset" to be adjusted
  // to maintain the correct relative position in the queued
  // data, so that a subsequent peek will retrieve the data that
  // would have been retrieved had the data not been removed.

  // For datagram sockets, if the "peek offset" points to the
  // middle of a packet, the data returned will be marked with
  // the MSG_TRUNC flag.

  // The following example serves to illustrate the use of
  // SO_PEEK_OFF.  Suppose a stream socket has the following
  // queued input data:

  //     aabbccddeeff

  // The following sequence of recv(2) calls would have the
  // effect noted in the comments:

  //     int ov = 4;                  // Set peek offset to 4
  //     setsockopt(fd, SOL_SOCKET, SO_PEEK_OFF, &ov, sizeof(ov));

  //     recv(fd, buf, 2, MSG_PEEK);  // Peeks "cc"; offset set to 6
  //     recv(fd, buf, 2, MSG_PEEK);  // Peeks "dd"; offset set to 8
  //     recv(fd, buf, 2, 0);         // Reads "aa"; offset set to 6
  //     recv(fd, buf, 2, MSG_PEEK);  // Peeks "ee"; offset set to 8
  PeekOff = SO_PEEK_OFF,

  // Return the credentials of the peer process connected to
  // this socket.  For further details, see unix(7).
  PeerCred = SO_PEERCRED,
  PeerCredentials = PeerCred,

  // Return the security context of the peer socket connected to
  // this socket.  For further details, see unix(7) and ip(7).
  PeerSec = SO_PEERSEC,
  PeerSecurity = PeerSec,

  // Set the protocol-defined priority for all packets to be
  // sent on this socket.  Linux uses this value to order the
  // networking queues: packets with a higher priority may be
  // processed first depending on the selected device queueing
  // discipline.  Setting a priority outside the range 0 to 6
  // requires the CAP_NET_ADMIN capability.
  Priority = SO_PRIORITY,

  // Retrieves the socket protocol as an integer, returning a
  // value such as IPPROTO_SCTP.  See socket(2) for details.
  // This socket option is read-only.
  Protocol = SO_PROTOCOL,

  // Sets or gets the maximum socket receive buffer in bytes.
  // The kernel doubles this value (to allow space for
  // bookkeeping overhead) when it is set using setsockopt(2),
  // and this doubled value is returned by getsockopt(2).  The
  // default value is set by the /proc/sys/net/core/rmem_default
  // file, and the maximum allowed value is set by the
  // /proc/sys/net/core/rmem_max file.  The minimum (doubled)
  // value for this option is 256.
  RcvBuf = SO_RCVBUF,
  RcvBuffer = RcvBuf,
  ReceiveBuffer = RcvBuffer,

  // Using this socket option, a privileged (CAP_NET_ADMIN)
  // process can perform the same task as SO_RCVBUF, but the
  // rmem_max limit can be overridden.
  RcvBufForce = SO_RCVBUFFORCE,
  RcvBufferForce = RcvBufForce,
  ReceiveBufferForce = RcvBufferForce,

  // Specify the minimum number of bytes in the buffer until the
  // socket layer will pass the data to the protocol
  // (SO_SNDLOWAT) or the user on receiving (SO_RCVLOWAT).
  // These two values are initialized to 1.  SO_SNDLOWAT is not
  // changeable on Linux (setsockopt(2) fails with the error
  // ENOPROTOOPT).  SO_RCVLOWAT is changeable only since Linux
  // 2.4.

  // Before Linux 2.6.28 select(2), poll(2), and epoll(7) did
  // not respect the SO_RCVLOWAT setting on Linux, and indicated
  // a socket as readable when even a single byte of data was
  // available.  A subsequent read from the socket would then
  // block until SO_RCVLOWAT bytes are available.  Since Linux
  // 2.6.28, select(2), poll(2), and epoll(7) indicate a socket
  // as readable only if at least SO_RCVLOWAT bytes are
  // available.
  RCVLOWAT = SO_RCVLOWAT,
  SNDLOWAT = SO_SNDLOWAT,

  // Specify the receiving or sending timeouts until reporting
  // an error.  The argument is a struct timeval.  If an input
  // or output function blocks for this period of time, and data
  // has been sent or received, the return value of that
  // function will be the amount of data transferred; if no data
  // has been transferred and the timeout has been reached, then
  // -1 is returned with errno set to EAGAIN or EWOULDBLOCK, or
  // EINPROGRESS (for connect(2)) just as if the socket was
  // specified to be nonblocking.  If the timeout is set to zero
  // (the default), then the operation will never timeout.
  // Timeouts only have effect for system calls that perform
  // socket I/O (e.g., accept(2), connect(2), read(2),
  // recvmsg(2), send(2), sendmsg(2)); timeouts have no effect
  // for select(2), poll(2), epoll_wait(2), and so on.
  RcvTimeO = SO_RCVTIMEO,
  SndTimeO = SO_SNDTIMEO,
  RcvTimeOut = RcvTimeOut,
  SndTimeOut = SndTimeOut,
  ReceiveTimeOut = ReceiveTimeOut,
  SendTimeOut = SendTimeOut,

  // Indicates that the rules used in validating addresses
  // supplied in a bind(2) call should allow reuse of local
  // addresses.  For AF_INET sockets this means that a socket
  // may bind, except when there is an active listening socket
  // bound to the address.  When the listening socket is bound
  // to INADDR_ANY with a specific port then it is not possible
  // to bind to this port for any local address.  Argument is an
  // integer boolean flag.
  ReuseAddr = SO_REUSEADDR,
  ReuseAddress = ReuseAddr,

  // Permits multiple AF_INET or AF_INET6 sockets to be bound to
  // an identical socket address.  This option must be set on
  // each socket (including the first socket) prior to calling
  // bind(2) on the socket.  To prevent port hijacking, all of
  // the processes binding to the same address must have the
  // same effective UID.  This option can be employed with both
  // TCP and UDP sockets.

  // For TCP sockets, this option allows accept(2) load
  // distribution in a multi-threaded server to be improved by
  // using a distinct listener socket for each thread.  This
  // provides improved load distribution as compared to
  // traditional techniques such using a single accept(2)ing
  // thread that distributes connections, or having multiple
  // threads that compete to accept(2) from the same socket.

  // For UDP sockets, the use of this option can provide better
  // distribution of incoming datagrams to multiple processes
  // (or threads) as compared to the traditional technique of
  // having multiple processes compete to receive datagrams on
  // the same socket.
  ReusePort = SO_REUSEPORT,

  // Indicates that an unsigned 32-bit value ancillary message
  // (cmsg) should be attached to received skbs indicating the
  // number of packets dropped by the socket since its creation.
  RXQ_OVFL = SO_RXQ_OVFL,

  // When this option is set on a socket, an error condition on
  // a socket causes notification not only via the exceptfds set
  // of select(2).  Similarly, poll(2) also returns a POLLPRI
  // whenever an POLLERR event is returned.

  // Background: this option was added when waking up on an
  // error condition occurred only via the readfds and writefds
  // sets of select(2).  The option was added to allow
  // monitoring for error conditions via the exceptfds argument
  // without simultaneously having to receive notifications (via
  // readfds) for regular data that can be read from the socket.
  // After changes in Linux 4.16, the use of this flag to
  // achieve the desired notifications is no longer necessary.
  // This option is nevertheless retained for backwards
  // compatibility.
  SELECT_ERR_QUEUE = SO_SELECT_ERR_QUEUE,

  // Sets or gets the maximum socket send buffer in bytes.  The
  // kernel doubles this value (to allow space for bookkeeping
  // overhead) when it is set using setsockopt(2), and this
  // doubled value is returned by getsockopt(2).  The default
  // value is set by the /proc/sys/net/core/wmem_default file
  // and the maximum allowed value is set by the
  // /proc/sys/net/core/wmem_max file.  The minimum (doubled)
  // value for this option is 2048.
  SndBuf = SO_SNDBUF,
  SndBuffer = SndBuf,
  SendBuf = SndBuf,
  SendBuffer = SndBuf,

  // Using this socket option, a privileged (CAP_NET_ADMIN)
  // process can perform the same task as SO_SNDBUF, but the
  // wmem_max limit can be overridden.
  SndBufForce = SO_SNDBUFFORCE,
  SndBufferForce = SndBufForce,
  SendBufForce = SndBufForce,
  SendBufferForce = SndBufForce,

  // Enable or disable the receiving of the SO_TIMESTAMP control
  // message.  The timestamp control message is sent with level
  // SOL_SOCKET and a cmsg_type of SCM_TIMESTAMP.  The cmsg_data
  // field is a struct timeval indicating the reception time of
  // the last packet passed to the user in this call.  See
  // cmsg(3) for details on control messages.
  TimeStamp = SO_TIMESTAMP,

  // Enable or disable the receiving of the SO_TIMESTAMPNS
  // control message.  The timestamp control message is sent
  // with level SOL_SOCKET and a cmsg_type of SCM_TIMESTAMPNS.
  // The cmsg_data field is a struct timespec indicating the
  // reception time of the last packet passed to the user in
  // this call.  The clock used for the timestamp is
  // CLOCK_REALTIME.  See cmsg(3) for details on control
  // messages.

  // A socket cannot mix SO_TIMESTAMP and SO_TIMESTAMPNS: the
  // two modes are mutually exclusive.
  TIMESTAMPNS = SO_TIMESTAMPNS,

  // Gets the socket type as an integer (e.g., SOCK_STREAM).
  // This socket option is read-only.
  Type = SO_TYPE,

  // Sets the approximate time in microseconds to busy poll on a
  // blocking receive when there is no data.  Increasing this
  // value requires CAP_NET_ADMIN.  The default for this option
  // is controlled by the /proc/sys/net/core/busy_read file.

  // The value in the /proc/sys/net/core/busy_poll file
  // determines how long select(2) and poll(2) will busy poll
  // when they operate on sockets with SO_BUSY_POLL set and no
  // events to report are found.

  // In both cases, busy polling will only be done when the
  // socket last received data from a network device that
  // supports this option.

  // While busy polling may improve latency of some
  // applications, care must be taken when using it since this
  // will increase both CPU utilization and power usage.
  BusyPoll = SO_BUSY_POLL,
};

}

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
  if (const auto status = getaddrinfo("www.google.com", "80", &hints, &info_ptr)
      ; status != 0) {
    gai_strerror(status); // ???
    throw std::runtime_error("");
  }

  std::unique_ptr<addrinfo, AddrInfo::ServerInfoDeleter> server_info(info_ptr);

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
  if (const auto status = getaddrinfo("www.google.com", "80", &hints, &info_ptr)
      ; status != 0) {
    gai_strerror(status); // ???
    throw std::runtime_error("");
  }

  auto s = socket(server_info->ai_family,
                  server_info->ai_socktype,
                  server_info->ai_protocol);
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
  const auto s = socket(server_info->ai_family,
                        server_info->ai_socktype,
                        server_info->ai_protocol);

  const auto send_flags = 0;
  const auto bytes_sent = send(s, bytes..., byte_count, send_flags);
  // VERIFY(bytes_sent != -1, "... {} ...", errno);

  const auto recv_flags = 0;
  const auto bytes_recvd = recv(s, buffer..., buffer_size, recv_flags);
  // VERIFY(bytes_recvd != -1, "... {} ...", errno);

  // bytes_recvd may be 0 under the following conditions:
  // - stream socket closed by peer
  // - datagram socket sent 0-sized packet
  // - requested bytes to receive was 0
}

TEST_CASE("`Sockets`::Datagram") {
  const auto s = socket(...);

  const auto send_res = sendto(s, bytes..., byte_count, send_flags, sockaddr_in, sizeof(sockaddr(?)));
  // VERIFY(send_res == -1, ...);
  const auto recv_res = recvfrom(s, buffer..., buffer_size, recv_flags, sockaddr, ...);
  // VERIFY(recv_res == -1, ...);
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
  // still need to `close(s)` to dispose of the file descriptor.
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

enum class RecvFlags {
  // Set the close-on-exec flag for the file descriptor received
  // via a UNIX domain file descriptor using the SCM_RIGHTS
  // operation (described in unix(7)).  This flag is useful for
  // the same reasons as the O_CLOEXEC flag of open(2).
  CMSG_CLOEXEC = MSG_CMSG_CLOEXEC, // recvmsg() only

  // Enables nonblocking operation; if the operation would
  // block, the call fails with the error EAGAIN or EWOULDBLOCK.
  // This provides similar behavior to setting the O_NONBLOCK
  // flag (via the fcntl(2) F_SETFL operation), but differs in
  // that MSG_DONTWAIT is a per-call option, whereas O_NONBLOCK
  // is a setting on the open file description (see open(2)),
  // which will affect all threads in the calling process as
  // well as other processes that hold file descriptors
  // referring to the same open file description.
  DontWait = MSG_DONTWAIT,

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
  ERRQUEUE = MSG_ERRQUEUE,

  // This flag requests receipt of out-of-band data that would
  // not be received in the normal data stream.  Some protocols
  // place expedited data at the head of the normal data queue,
  // and thus this flag cannot be used with such protocols.
  OutOfBand = MSG_OOB,
  OOB = OutOfBand,

  // This flag causes the receive operation to return data from
  // the beginning of the receive queue without removing that
  // data from the queue.  Thus, a subsequent receive call will
  // return the same data.
  Peek = MSG_PEEK,

  // For raw (AF_PACKET), Internet datagram (since Linux
  // 2.4.27/2.6.8), netlink (since Linux 2.6.22), and UNIX
  // datagram as well as sequenced-packet (since Linux 3.4)
  // sockets: return the real size of the packet or datagram,
  // even when it was longer than the passed buffer.

  // For use with Internet stream sockets, see tcp(7).
  TRUNC = MSG_TRUNC,

  // This flag requests that the operation block until the full
  // request is satisfied.  However, the call may still return
  // less data than requested if a signal is caught, an error or
  // disconnect occurs, or the next data to be received is of a
  // different type than that returned.  This flag has no effect
  // for datagram sockets.
  WAITALL = MSG_WAITALL,
};
