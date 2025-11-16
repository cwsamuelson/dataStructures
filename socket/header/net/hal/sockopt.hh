#pragma once

#include "net/hal/protocols.hh"

namespace flp::Net {

// https://www.man7.org/linux/man-pages/man7/socket.7.html
// setsockopt
// with SOL_SOCKET
enum class Options {
  AcceptConn = SO_ACCEPTCONN,
  AcceptConnection = AcceptConn,

  AttachFilter = SO_ATTACH_FILTER,
  AttachBPF = SO_ATTACH_BPF,

  AttachReusePortCBPF = SO_ATTACH_REUSEPORT_CBPF,
  AttachReusePortEBPF = SO_ATTACH_REUSEPORT_EBPF,

  BindToDevice = SO_BINDTODEVICE,

  Broadcast = SO_BROADCAST,

  BSDCompat = SO_BSDCOMPAT,

  Debug = SO_DEBUG,

  DetachFilter = SO_DETACH_FILTER,
  DetachBPF = SO_DETACH_BPF,

  Domain = SO_DOMAIN,

  Error = SO_ERROR,

  DontRoute = SO_DONTROUTE,

  IncomingCPU = SO_INCOMING_CPU,

  IncomingNAPIID = SO_INCOMING_NAPI_ID,

  KeepAlive = SO_KEEPALIVE,

  Linger = SO_LINGER,

  LockFilter = SO_LOCK_FILTER,

  Mark = SO_MARK,

  OOBInline = SO_OOBINLINE,
  OutOfBandInline = OOBInline,

  // AF_UNIX specific

  PassCred = SO_PASSCRED,
  PassCredentials = PassCred,

  PassSec = SO_PASSSEC,
  PassSecurity = PassSec,

  PeekOff = SO_PEEK_OFF,

  PeerCred = SO_PEERCRED,
  PeerCredentials = PeerCred,

  PeerSec = SO_PEERSEC,
  PeerSecurity = PeerSec,

  // end AF_UNIX specific

  Priority = SO_PRIORITY,

  Protocol = SO_PROTOCOL,

  RcvBuf = SO_RCVBUF,
  RcvBuffer = RcvBuf,
  ReceiveBuffer = RcvBuffer,

  RcvBufForce = SO_RCVBUFFORCE,
  RcvBufferForce = RcvBufForce,
  ReceiveBufferForce = RcvBufferForce,

  RcvLowAt = SO_RCVLOWAT,
  ReceiveLowAt = RcvLowAt,

  SndLowAt = SO_SNDLOWAT,
  SendLowAt = SndLowAt,

  RcvTimeO = SO_RCVTIMEO,
  RcvTimeOut = RcvTimeO,
  ReceiveTimeOut = RcvTimeOut,

  SndTimeO = SO_SNDTIMEO,
  SndTimeOut = SndTimeO,
  SendTimeOut = SndTimeOut,

  ReuseAddr = SO_REUSEADDR,
  ReuseAddress = ReuseAddr,

  ReusePort = SO_REUSEPORT,

  RXQ_OVFL = SO_RXQ_OVFL,

  SelectErrQueue = SO_SELECT_ERR_QUEUE,
  SelectErrorQueue = SO_SELECT_ERR_QUEUE,

  SndBuf = SO_SNDBUF,
  SndBuffer = SndBuf,
  SendBuf = SndBuf,
  SendBuffer = SndBuf,

  SndBufForce = SO_SNDBUFFORCE,
  SndBufferForce = SndBufForce,
  SendBufForce = SndBufForce,
  SendBufferForce = SndBufForce,

  TimeStamp = SO_TIMESTAMP,

  TimeStampNS = SO_TIMESTAMPNS,

  Type = SO_TYPE,

  BusyPoll = SO_BUSY_POLL,
};

enum class SockOptError {
  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
  BadFileDescriptor = BadFile,

  Fault = EFAULT,

  Inval = EINVAL,
  Invalid = Inval,

  NoProtoOpt = ENOPROTOOPT,
  NoProtoOption = NoProtoOpt,
  NoProtocolOption = NoProtoOption,

  NotSock = ENOTSOCK,
  NotSocket = NotSock,
};

void getsockopt() {
}

void setsockopt() {
}

}
