#pragma once

//#include <nlohmann/json.hpp>

#include <concepts>
#include <filesystem>
#include <string>

// In addition to my own ideas for how configuration should be handled, this resource tries to do some similar things:
// https://github.com/doom/nectarine
// ultimately those ideas are very similar to mine, but they have a decent API, imo.

namespace flp {

namespace Providers {

template<typename Type, typename Target>
concept Provider = requires(Type value) {
  {value()} -> std::same_as<Target>;
};

template<typename Target>
struct CommandLine;

template<typename Target>
struct Environment {
  std::string prefix;

  /*Target operator()() {
  }*/
};

template<typename Target>
struct Json {
  std::filesystem::path file_name;

  /*Target operator()() {
    return nlohmann::json::parse(file_name);
  }*/
};

template<typename Target>
struct Yaml {
  std::filesystem::path file_name;

  /*Target operator()() {
    return yaml::parse(file_name);
  }*/
};

}

struct Configuration {};

} // namespace flp
