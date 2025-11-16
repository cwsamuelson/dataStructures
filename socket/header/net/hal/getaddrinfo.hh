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
