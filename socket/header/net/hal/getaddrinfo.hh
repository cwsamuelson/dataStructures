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

  IDN = AI_IDN,

  CanonIDN = AI_CANONIDN,

  IDNAAllowUnassigned = AI_IDN_ALLOW_UNASSIGNED,
  IDNAUseSTD3ASCIIRules = AI_IDN_USE_STD3_ASCII_RULES,
};

enum class Error {
  Success = 0,
 
  AddrFamily = EAI_ADDRFAMILY,
  AddressFamily = AddrFamily,
 
  Again = EAI_AGAIN,
  TryAgain = Again,
  TryLater = TryAgain,
 
  BadFlags = EAI_BADFLAGS,
 
  Fail = EAI_FAIL,
 
  Family = EAI_FAMILY,
  InvalidFamily = Family,
  UnsupportedFamily = InvalidFamily,
 
  Memory = EAI_MEMORY,
  OutOfMemory = Memory,
  OOM = OutOfMemory,
 
  NoData = EAI_NODATA,
 
  NoName = EAI_NONAME,
 
  Service = EAI_SERVICE,
 
  SockType = EAI_SOCKTYPE,
 
  System = EAI_SYSTEM,
  CheckErroNo = System,
  CheckErroNumber = CheckErroNo,
};

}

int getaddrinfo(const char* restrict node,
                const char* service,
                const addrinfo* hints,
                addrinfo** res);

struct addrinfo {
  int       ai_flags;
  int       ai_family;
  int       ai_socktype;
  int       ai_protocol;
  socklen_t ai_addrlen;
  sockaddr* ai_addr;
  char*     ai_canonname;
  addrinfo* ai_next;
};

void getaddrinfo(std::string_view host, std::string_view service);

void getaddrinfo(std::string_view host, uint16_t port);

}
