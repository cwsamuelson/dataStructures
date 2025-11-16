#pragma once

#include <bitflags/bitflags.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstdint>
#include <string>
#include <vector>

namespace flp::Net {

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

template <typename Type>
struct AddrInfoFlagsImpl {
  using flag = bf::internal::raw_flag<AddrInfoFlagsImpl, Type>;
  static constexpr int begin_ = __LINE__;

  static constexpr flag None{ 0 };
  static constexpr flag Passive{ AI_PASSIVE };
  static constexpr flag NumericServ{ AI_NUMERICSERV };
  static constexpr flag NumericService{ NumericServ };
  static constexpr flag CanonName{ AI_CANONNAME };
  static constexpr flag CanonicalName{ CanonName };
  static constexpr flag AddrConfig{ AI_ADDRCONFIG };
  static constexpr flag AddressConfig{ AddrConfig };
  static constexpr flag V4Mapped{ AI_V4MAPPED };
  static constexpr flag All{ AI_ALL };
  static constexpr flag IDN{ AI_IDN };
  static constexpr flag CanonIDN{ AI_CANONIDN };
  static constexpr flag IDNAAllowUnassigned{ AI_IDN_ALLOW_UNASSIGNED };
  static constexpr flag IDNAUseSTD3ASCIIRules{ AI_IDN_USE_STD3_ASCII_RULES };

  static constexpr int end_   = __LINE__;
};

using AddrInfoFlags = bf::bitflags<
  AddrInfoFlagsImpl<bf::bitflags<AddrInfoFlagsImpl<uint8_t>>::underlying_type>,
  bf::bitflags<AddrInfoFlagsImpl<uint8_t>>::underlying_type,
  bf::internal::raw_flag
>;

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

struct Service {
  Service(const char* srvc)
    : Service(std::string(srvc))
  {}

  Service(std::string srvc)
    : service(std::move(srvc))
  {}

  Service(const uint16_t port)
    : service(std::to_string(port))
  {}

  std::string service;
};

struct ConnectionParameters {
  Family family;
  SocketType type;
  Protocol protocol;
};

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const Service& service, 
  Family family, 
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service,
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const Service& service, 
  Family family, 
  SocketType type,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service,
  const SocketType type,
  const AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  Family family, 
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  Family family, 
  SocketType type,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const SocketType type,
  const AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service
);

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service, 
  Family family, 
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service,
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service, 
  Family family, 
  SocketType type,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service,
  SocketType type,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
);

std::vector<ConnectionParameters> getaddrinfo(
  Family family, 
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  SocketType type
);

std::vector<ConnectionParameters> getaddrinfo(
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  Family family, 
  SocketType type,
  AddrInfoFlags flags
);

std::vector<ConnectionParameters> getaddrinfo(
  SocketType type,
  AddrInfoFlags flags
);

}
