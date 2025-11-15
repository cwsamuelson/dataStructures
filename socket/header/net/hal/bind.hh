#pragma once

namespace flp::Net {

enum class BindError {
  // The address is protected, and the user is not the superuser.
  Acces = EACCES,
  Access = Acces,
 
  // The given address is already in use.

  // (Internet domain sockets) The port number was specified as
  // zero in the socket address structure, but, upon attempting
  // to bind to an ephemeral port, it was determined that all
  // port numbers in the ephemeral port range are currently in
  // use.  See the discussion of
  // /proc/sys/net/ipv4/ip_local_port_range ip(7).
  ADDRINUSE = EADDRINUSE,

  // sockfd is not a valid file descriptor.
  BadF = EBADF,
  BadFD = BadF,
  BadFile = BadFD,
  BadFileDescriptor = BadFile,

  // The socket is already bound to an address.

  // addrlen is wrong, or addr is not a valid address for this
  // socket's domain.
  Inval = EINVAL,
  Invalid = Inval,
  InvalidAddress = Invalid,
 
  // The file descriptor sockfd does not refer to a socket.
  NotSock = ENOTSOCK,
 
  // A nonexistent interface was requested or the requested
  // address was not local.
  AddrNotAvail = EADDRNOTAVAIL,
  AddrNotAvailable = AddrNotAvail,
  AddressNotAvail = AddrNotAvail,
  AddressNotAvailable = AddrNotAvail,
 
  // UNIX domain (AF_UNIX) socket specific
 
  // EACCES Search permission is denied on a component of the path
  //        prefix.  (See also path_resolution(7).)

  // addr points outside the user's accessible address space.
  Fault = EFAULT,

  // Too many symbolic links were encountered in resolving addr.
  Loop = ELOOP,
 
  // address too long
  NameTooLong = ENAMETOOLONG,
  NameTooLong = ENAMETOOLONG,
 
  // A component in the directory prefix of the socket pathname does not exist.
  NoEnt = ENOENT,
  NoEntry = NoEnt,

  // Insufficient kernel memory was available.
  NoMem = ENOMEM,
  NoMemory = NoMem,
 
  // A component of the path prefix is not a directory.
  NotDir = ENOTDIR,
  NotDirectory = NotDir,

  // The socket inode would reside on a read-only filesystem.
  ROFS = EROFS,
  ReadOnly = ROFS,
 
  // Protocol specific errors may be generated
};

void foo() {
  auto bind_res = bind(s, server_info->ai_addr, server_info, ai_addrlen);
  // VERIFY(bind_res != -1, "... {} ...", errno);
}

}
