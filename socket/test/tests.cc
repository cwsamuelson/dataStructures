#include <catch2/catch_all.hpp>

#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <print>

#define BUF_SIZE 500

// using namespace flp;

std::map<std::string, size_t> protocols;
std::multimap<size_t, std::string> protocol_names;

void get_protocols() {
  protoent *proto;

  // Open the protocol database
  setprotoent(1); // 1 means stay open

  // Read entries until EOF
  while ((proto = getprotoent()) != nullptr) {
    // printf("Name: %s\n", proto->p_name);
    // printf("Aliases: ");
    for (char **alias = proto->p_aliases; *alias != nullptr; alias++) {
      protocols[*alias] = proto->p_proto;
      protocol_names.emplace(proto->p_proto, *alias);
      // printf("%s ", *alias);
    }
    // printf("\nProtocol Number: %d\n\n", proto->p_proto);
  }

  // Close the protocol database
  endprotoent();
}

void print_family(const auto family) {
  if (family == AF_INET) {
    std::println("\tfamily: IPV4");
  } else if (family == AF_INET6) {
    std::println("\tfamily: IPV6");
  } else if (family == AF_UNSPEC) {
    std::println("\tfamily: UNSPEC");
  } else {
    std::println("\tfamily: Unknown: {}", family);
  }
}

void print_sock_type(const auto type) {
  if (type == SOCK_STREAM) {
    std::println("\tsocket type: STREAM");
  } else if (type == SOCK_DGRAM) {
    std::println("\tsocket type: DGRAM");
  } else if (type == 0) {
    std::println("\tsocket type: Unspecified");
  } else {
    std::println("\tsocket type: Unknown: {}", type);
  }
}

void print_protocol(const auto protocol) {
  for (auto begin = protocol_names.lower_bound(protocol);
            begin != protocol_names.upper_bound(protocol);
            ++begin) {
    std::println("\tprotocol: {}", begin->second);
  }
}

void do_thing(auto&& ...args) {
  int       sfd;
  addrinfo* result = nullptr;

  auto s = getaddrinfo(args..., &result);
  if (s != 0) {
    std::println("getaddrinfo: {}", gai_strerror(s));
    CHECK(false);
    return;
  }

  if (result == nullptr) {
    std::println("getaddrinfo returned no results");
  }

  for (addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {
    std::println("\tflags: {}", rp->ai_flags);
    print_family(rp->ai_family);
    print_sock_type(rp->ai_socktype);
    print_protocol(rp->ai_protocol);
    // IPV4
    if (rp->ai_family == AF_INET) {
      const auto* ipv4_addr = (sockaddr_in*)rp->ai_addr;
      std::println("\tv4: {}:{}", ipv4_addr->sin_addr.s_addr, ipv4_addr->sin_port);
    // IPV6
    } else if (rp->ai_family == AF_INET6) {
      const auto* ipv6_addr = (sockaddr_in6*)rp->ai_addr;
      std::println("\tv6: {}:{}", ipv6_addr->sin6_addr.s6_addr, ipv6_addr->sin6_port);
    }
    if (rp->ai_canonname != nullptr) {
      std::println("\t\tcanon: {}", rp->ai_canonname);
    }
    std::println("\tnext: {}", (void*)rp->ai_next);

    sfd = socket(rp->ai_family, rp->ai_socktype,
                 rp->ai_protocol);

    if (sfd == -1)
        continue;

    // if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
    //     break;                  /* Success */
    if (s = bind(sfd, rp->ai_addr, rp->ai_addrlen); s == 0) {
      std::println("Bind success");
    } else {
      std::println("Bind failed: {}", gai_strerror(s));
    }

    close(sfd);
  }

  freeaddrinfo(result);           /* No longer needed */
  close(sfd);
}

void do_thing0() {
  std::println("{}", __FUNCTION__);
  addrinfo         hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  std::println("nullptr, \"80\", &hints");
  do_thing(nullptr, "80", &hints);
}

void do_thing1() {
  std::println("{}", __FUNCTION__);
  addrinfo         hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  std::println("nullptr, \"8080\", &hints");
  do_thing(nullptr, "8080", &hints);
}

// name or service not known
void do_thing2() {
  std::println("{}", __FUNCTION__);
  addrinfo         hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  std::println("nullptr, nullptr, &hints");
  do_thing(nullptr, nullptr, &hints);
}

void do_thing3() {
  std::println("{}", __FUNCTION__);
  addrinfo         hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = 0;          /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  std::println("nullptr, \"80\", &hints");
  do_thing(nullptr, "80", &hints);
}

void do_thing4() {
  std::println("{}", __FUNCTION__);
  std::println("nullptr, \"80\", nullptr");
  do_thing(nullptr, "80", nullptr);
}

void do_thing5() {
  std::println("{}", __FUNCTION__);
  std::println("nullptr, \"8080\", nullptr");
  do_thing(nullptr, "8080", nullptr);
}

void do_thing6() {
  std::println("{}", __FUNCTION__);
  std::println("\"www.google.com\", \"8080\", nullptr");
  do_thing("www.google.com", "8080", nullptr);
}

// name or service not known
void do_thing7() {
  std::println("{}", __FUNCTION__);
  std::println("nullptr, nullptr, nullptr");
  do_thing(nullptr, nullptr, nullptr);
}

// name or service not known
void do_thing8() {
  std::println("{}", __FUNCTION__);
  addrinfo         hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = 0;          /* unspecified socket type */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  std::println("nullptr, nullptr, &hints");
  do_thing(nullptr, nullptr, &hints);
}

void do_things() {
  std::println("{}", __FUNCTION__);
  addrinfo         hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = 0;          /* unspecified socket type */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  for (const auto host : { "www.google.com", "example.com", (const char*)nullptr }) {
    const auto host_str = std::format("{}", host != nullptr ? host : "nullptr");

    for (const auto port : { "80", "8080", (const char*)nullptr }) {
      const auto port_str = std::format("{}", port != nullptr ? port : "nullptr");

      for (const auto hint : { &hints, (addrinfo*)nullptr }) {
        const auto hint_str = std::format("{}", port != nullptr ? "nullptr" : "&hints");

        std::println("{}, {}, {}", host_str, port_str, hint_str);

        do_thing(host, port, hint);
      }
    }
  }
}

TEST_CASE("`Sockets`::...") {
  // DNS/addrinfo

  get_protocols();

  do_thing0();
  do_thing1();
  do_thing2();
  do_thing3();
  do_thing4();
  do_thing5();
  do_thing6();
  do_thing7();
  do_thing8();
  do_things();

  CHECK(false);
}
