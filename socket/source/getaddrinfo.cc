#include "net/hal/getaddrinfo.hh"

#include <error_help.hh>

#include <cstring>
#include <memory>

namespace flp::Net {

namespace {

struct ServerInfoDeleter {
  void operator()(addrinfo* info) {
    freeaddrinfo(info);
  }
};

using AddrInfoPointer = std::unique_ptr<addrinfo, ServerInfoDeleter>;

auto getaddrinfo_impl(
  const auto& host, 
  const auto& service, 
  const int family, 
  const int type,
  const int flags
) {
  addrinfo hints;
  addrinfo* info_ptr = nullptr;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = family;
  hints.ai_socktype = type;
  hints.ai_flags = flags;

  if (const auto status = getaddrinfo(host, service, &hints, &info_ptr)
      ; status != 0) {
    VERIFY("getaddrinfo(host.c_str(), service.c_str(), &hints, &info_ptr) == 0" or false,
           "getaddrinfo({}, {}, ...) failed: {}",
           host, service, gai_strerror(status));
  }

  AddrInfoPointer server_info(info_ptr);

  std::vector<ConnectionParameters> connections;
  for (addrinfo* cursor = server_info.get(); cursor != nullptr; cursor = cursor->ai_next) {
    connections.push_back(ConnectionParameters {
      (Family)cursor->ai_family,
      (SocketType)cursor->ai_socktype,
      (Protocol)cursor->ai_protocol
    });
  }

  return connections;
}

}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service
) {
  return getaddrinfo(host, service, Family::Unspecified, SocketType::Unspecified, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const Service& service, 
  const Family family, 
  const SocketType type
) {
  return getaddrinfo(host, service, family, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service,
  SocketType type
) {
  return getaddrinfo(host, service, Family::Unspecified, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service,
  const AddrInfoFlags flags
) {
  return getaddrinfo(host, service, Family::Unspecified, SocketType::Unspecified, flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const Service& service, 
  const Family family, 
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo_impl(host.c_str(), service.service.c_str(), (int)family, (int)type, flags.bits());
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const Service& service,
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo(host, service, Family::Unspecified, type, flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host
) {
  return getaddrinfo(host, Family::Unspecified, SocketType::Unspecified, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const Family family, 
  const SocketType type
) {
  return getaddrinfo(host, family, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const SocketType type
) {
  return getaddrinfo(host, Family::Unspecified, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const AddrInfoFlags flags
) {
  return getaddrinfo(host, Family::Unspecified, SocketType::Unspecified, flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const Family family, 
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo_impl(host.c_str(), nullptr, (int)family, (int)type, flags.bits());
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo(host, Family::Unspecified, type, flags);
}






// std::vector<ConnectionParameters> getaddrinfo(
//   const Service& service, 
//   const Family family, 
//   const SocketType type,
//   const AddrInfoFlags flags
// );

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service
) {
  return getaddrinfo(service, SocketType::Unspecified);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service, 
  const Family family, 
  const SocketType type
) {
  return getaddrinfo(service, family, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service,
  const SocketType type
) {
  return getaddrinfo(service, Family::Unspecified, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service,
  const AddrInfoFlags flags
) {
  return getaddrinfo(service, Family::Unspecified, SocketType::Unspecified, flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service, 
  const Family family, 
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo_impl(nullptr, service.service.c_str(), (int)family, (int)type, (int)flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Service& service,
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo(service, Family::Unspecified, type, flags);
}


std::vector<ConnectionParameters> getaddrinfo(
) {
  return getaddrinfo(Family::Unspecified, SocketType::Unspecified, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Family family, 
  const SocketType type
) {
  return getaddrinfo(family, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const SocketType type
) {
  return getaddrinfo(Family::Unspecified, type, AddrInfoFlags::None);
}

std::vector<ConnectionParameters> getaddrinfo(
  const AddrInfoFlags flags
) {
  return getaddrinfo(Family::Unspecified, SocketType::Unspecified, flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const Family family, 
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo_impl(nullptr, nullptr, (int)family, (int)type, (int)flags);
}

std::vector<ConnectionParameters> getaddrinfo(
  const SocketType type,
  const AddrInfoFlags flags
) {
  return getaddrinfo(Family::Unspecified, type, flags);
}

}
