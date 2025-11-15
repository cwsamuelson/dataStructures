#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace flp::Net {

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

void foo () {
  addrinfo hints{};
  addrinfo* info_ptr = nullptr;
  char ipstr[INET6_ADDRSTRLEN];

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  // VERIFY(getaddrinfo("www.google.com", "80", &hints, &info_ptr) == 0, "{}", gai_strerror(status));
  if (const auto status = getaddrinfo("www.google.com", "80", &hints, &info_ptr)
      ; status != 0) {
    gai_strerror(status);
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
}

}
