#pragma once

#include "core/layer.hh"

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace Core {

using Arguments = std::vector<std::string_view>;
using Environment = std::map<std::string_view, std::string_view>;

struct ApplicationBase {
  // fluent interface to configure
  struct Config {
    std::string name;
    std::filesystem::path location;

    Config&& set_name(std::string value) &&;
    Config&& set_location(std::filesystem::path value) &&;
  };

  ApplicationBase(Config conf);
  explicit
  ApplicationBase(const char* name);
  explicit
  ApplicationBase(std::string name);
  explicit
  ApplicationBase(std::filesystem::path location);
  ApplicationBase(std::string name, std::filesystem::path location);

  virtual ~ApplicationBase();

  virtual void run();

  virtual void run(const Arguments& arguments);

  virtual void run(const Arguments& arguments, const Environment& environment);

  void push(std::shared_ptr<Layer> layer);

  template<typename LayerType, typename... Args>
    requires std::derived_from<Layer, LayerType>
  void create(Args&& ...args) {
    layers_stack.emplace_back(std::make_shared<LayerType>(std::forward<Args>(args)...));
  }

  Config config;
  std::vector<std::shared_ptr<Layer>> layers_stack;
};

}