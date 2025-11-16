#include "net/hal/getaddrinfo.hh"

#include <error_help.hh>

#include <cstring>
#include <memory>

namespace flp::Net {

struct ServerInfoDeleter {
  void operator()(addrinfo* info) {
    freeaddrinfo(info);
  }
};

using AddrInfoPointer = std::unique_ptr<addrinfo, ServerInfoDeleter>;

std::vector<ConnectionParameters> getaddrinfo() {
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

  AddrInfoPointer server_info(info_ptr);

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

    // std::println("\t{}: {}", ipver, ipstr);
  }
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const std::string& service
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  uint16_t port
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const std::string& service, 
  Family family, 
  SocketType type
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  uint16_t port,
  Family family,
  SocketType type
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  uint16_t port,
  SocketType type
) {
  return {};
}


std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  const std::string& service,
  AddrInfoFlags flags
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  uint16_t port,
  AddrInfoFlags flags
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host, 
  const std::string& service, 
  Family family, 
  SocketType type,
  AddrInfoFlags flags
) {
  addrinfo hints;
  addrinfo* info_ptr = nullptr;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = (int)family;
  hints.ai_socktype = (int)type;
  hints.ai_flags = flags.bits();

  if (const auto status = getaddrinfo(host.c_str(), service.c_str(), &hints, &info_ptr)
      ; status != 0) {
    VERIFY("getaddrinfo(host.c_str(), service.c_str(), &hints, &info_ptr) == 0" or false,
           "getaddrinfo({}, {}, ...) failed: {}",
           host, service, gai_strerror(status));
  }

  AddrInfoPointer server_info(info_ptr);

  std::vector<ConnectionParameters> connections;
  for (addrinfo* cursor = server_info.get(); cursor != nullptr; cursor = cursor->ai_next) {
    connections.push_back(ConnectionParameters{
      (Family)cursor->ai_family,
      (SocketType)cursor->ai_socktype,
      (Protocol)cursor->ai_protocol
    });
  }

  return connections;
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  uint16_t port,
  Family family,
  SocketType type,
  AddrInfoFlags flags
) {
  return {};
}

std::vector<ConnectionParameters> getaddrinfo(
  const std::string& host,
  uint16_t port,
  SocketType type,
  AddrInfoFlags flags
) {
  return {};
}

}
