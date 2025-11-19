#include <lyra/lyra.hpp>
#include <nlohmann/json.hpp>

#include <testing/framework.hh>

#include <iostream>
#include <vector>

using namespace flp;

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

    std::cout << tests.dump();

    return 0;
  }

  std::cout << "@@@@@ RUNNING THE TESTS, I GUESS????\n";

  return 0;
}
