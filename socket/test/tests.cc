#include <catch2/catch_all.hpp>

#include <net/hal/getaddrinfo.hh>

using namespace flp;

// In terms of unit tests this is very weird.  It's probably more reliable in a
// virtualized or otherwise contained environment (docker container).  I will
// try to constrain the tests to simple things that provide more reliable results.
TEST_CASE("`Sockets`::getaddrinfo") {
  SECTION("Constrained") {
    const auto conn_params = Net::getaddrinfo(
      "localhost", "80",
      Net::Family::IPV4,
      Net::SocketType::Stream,
      Net::AddrInfoFlags::Passive
    );

    CHECK(not conn_params.empty());
    CHECK(conn_params.size() == 2);

    CHECK(conn_params.at(0).family == Net::Family::IPV4);
    CHECK(conn_params.at(1).family == Net::Family::IPV4);
    CHECK(conn_params.at(0).type == Net::SocketType::Stream);
    CHECK(conn_params.at(1).type == Net::SocketType::Stream);
    // CHECK(conn_params.at(0).protocol == Net::Protocol::...);
    // CHECK(conn_params.at(1).protocol == Net::Protocol::...);
  }

  SECTION("No port") {
    using namespace std::literals;
    const auto conn_params = Net::getaddrinfo(
      "localhost"s,
      Net::Family::IPV4,
      Net::SocketType::Stream,
      Net::AddrInfoFlags::Passive
    );

    CHECK(not conn_params.empty());
    CHECK(conn_params.size() == 2);

    CHECK(conn_params.at(0).family == Net::Family::IPV4);
    CHECK(conn_params.at(1).family == Net::Family::IPV4);
    CHECK(conn_params.at(0).type == Net::SocketType::Stream);
    CHECK(conn_params.at(1).type == Net::SocketType::Stream);
    // CHECK(conn_params.at(0).protocol == Net::Protocol::...);
    // CHECK(conn_params.at(1).protocol == Net::Protocol::...);
  }

  SECTION("No host") {
    SECTION("Constrained") {
      using namespace std::literals;
      const auto conn_params = Net::getaddrinfo(
        flp::Net::Service("8080"),
        Net::Family::IPV4,
        Net::SocketType::Stream,
        Net::AddrInfoFlags::Passive
      );

      CHECK(not conn_params.empty());
      CHECK(conn_params.size() == 1);

      CHECK(conn_params.at(0).family == Net::Family::IPV4);
      CHECK(conn_params.at(0).type == Net::SocketType::Stream);
      // CHECK(conn_params.at(0).protocol == Net::Protocol::...);
    }

    SECTION("Unconstrained") {
      using namespace std::literals;
      const auto conn_params = Net::getaddrinfo(
        flp::Net::Service("8080"),
        Net::Family::Unspecified,
        Net::SocketType::Unspecified,
        Net::AddrInfoFlags::None
      );

      CHECK(not conn_params.empty());
      CHECK(conn_params.size() == 6);
    }
  }
}
