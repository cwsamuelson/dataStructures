#include <abstract/values.hh>

#include <catch2/catch_all.hpp>

#include <map>
#include <string>
#include <vector>

using namespace flp;

TEST_CASE("`Abstract`::`Values`") {
  {
    Abstract::Value value;

    value = "";
    value = true;
    value = 1;
    value = -1;
    // value = std::vector<int>{};
    // value = std::map<std::string, int>{};
    value = nullptr;
  }

  {
    Abstract::Value value{""};
  }

  {
    Abstract::Value value{true};
  }

  {
    Abstract::Value value{1};
  }

  {
    Abstract::Value value{-1};
  }

  // {
  //   {
  //     Abstract::Value value{std::vector<int>{}};
  //   }
  //   {
  //     Abstract::Value value{std::vector<unsigned int>{}};
  //   }
  //   {
  //     Abstract::Value value{std::vector<double>{}};
  //   }
  //   {
  //     Abstract::Value value{std::vector<std::string>{}};
  //   }
  // }

  // {
  //   {
  //     Abstract::Value value{std::map<std::string, int>};
  //   }
  //   {
  //     Abstract::Value value{std::map<std::string, unsigned int>};
  //   }
  //   {
  //     Abstract::Value value{std::map<std::string, double>};
  //   }
  //   {
  //     Abstract::Value value{std::map<std::string, std::string>};
  //   }
  // }

  {
    Abstract::Value value{nullptr};
  }
}
