#pragma once

namespace flp::Net {

enum class BindError {
  Acces = EACCES,
  Access = Acces,
 
  AddrInUse = EADDRINUSE,
  AddressInUse = AddrInUse,

  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
  BadFileDescriptor = BadFile,

  Inval = EINVAL,
  Invalid = Inval,
  InvalidAddress = Invalid,
 
  NotSock = ENOTSOCK,
 
  AddrNotAvail = EADDRNOTAVAIL,
  AddrNotAvailable = AddrNotAvail,
  AddressNotAvail = AddrNotAvail,
  AddressNotAvailable = AddrNotAvail,
 
  Fault = EFAULT,

  Loop = ELOOP,
 
  NameTooLong = ENAMETOOLONG,
  NameTooLong = ENAMETOOLONG,
 
  NoEnt = ENOENT,
  NoEntry = NoEnt,

  NoMem = ENOMEM,
  NoMemory = NoMem,
 
  NotDir = ENOTDIR,
  NotDirectory = NotDir,

  ROFS = EROFS,
  ReadOnly = ROFS,
 
  // Protocol specific errors may be generated
};

void foo() {
  auto bind_res = bind(s, server_info->ai_addr, server_info, ai_addrlen);
  // VERIFY(bind_res != -1, "... {} ...", errno);
}

}
