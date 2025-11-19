#include <lyra/lyra.hpp>
#include <nlohmann/json.hpp>

#include <testing/framework.hh>
#include <testing/test_registry.hh>

#include <iostream>
#include <vector>

using namespace flp;

#include <print>

int main(int argc, char* argv[]) {
  bool show_help = false;
  bool list_tests = false;

  auto cli = lyra::help(show_help)
    | lyra::opt(list_tests)
      ["--list-tests"]("list the tests")
  ;

  const auto result = cli.parse({argc, argv});

  if (not result) {
    std::cout << result.message() << '\n';
    return 1;
  }

  if (show_help) {
    std::cout << cli << '\n';
    return 0;
  }

  if (list_tests) {
    nlohmann::json tests;

    tests["version"] = 1;
    tests["tests"] = std::vector<nlohmann::json>{};

    for (const auto& [name, _] : flp::TestRegistry::instance().tests) {
      tests["tests"].push_back(name);
    }

    std::cout << tests.dump();

    return 0;
  }

  for (size_t i = 0; i < argc; ++i) {
    std::println("{}: {}", i, argv[i]);
  }

  for (const auto& [name, test] : flp::TestRegistry::instance().tests) {
    try {
      test();
    } catch(const std::exception& e) {
      std::cout << "Foo threw an exception!:\t" << e.what() << "\nTests failed :(";

      return 1;
    } catch(...) {
      std::cout << "Foo threw an exception!  Tests failed :(";

      return 1;
    }
  }

  return 0;
}
