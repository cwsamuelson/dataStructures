#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace flp::Net {

//!@TODO `socketpair`

using Socket = int;

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
  Stream = SOCK_STREAM,

  Dgram = SOCK_DGRAM,
  Datagram = Dgram,

  SeqPacket = SOCK_SEQPACKET,
  SequencedPacket = SeqPacket,

  Raw = SOCK_RAW,

  RDM = SOCK_RDM,

  Packet = SOCK_PACKET,
};

enum class Type2 {
  NonBlock = SOCK_NONBLOCK,
  NonBlocking,

  // FD_CLOEXEC
  //  O_CLOEXEC
  CloExec = SOCK_CLOEXEC,
  CloseExec = CloExec,
  CloseOnExec = CloseExec,
};

enum class Error {
  Acces = EACCES,
  Access = Acces,
  NoPermission = Access,

  AFNoSupport = EAFNOSUPPORT,
  FamNoSupport = AFNoSupport,
  FamilyNoSupport = FamNoSupport,
  FamilyNotSupported = FamilyNoSupport,

  Inval = EINVAL,
  Invalid = Inval,

  MFile = EMFILE,

  NFile = ENFILE,

  NoBufs = ENOBUFS,
  NoBuffers = NoBufs,

  NoMem = ENOMEM,
  NoMemory = NoMem,

  ProtoNoSupport = EPROTONOSUPPORT,
  ProtocolNotSupported = ProtoNoSupport,
};

void foo() {
}

}
