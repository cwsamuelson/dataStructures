#include "core/application.hh"

namespace Core {

ApplicationBase::Config&& ApplicationBase::Config::set_name(std::string value) && {
  name = std::move(value);
  return std::move(*this);
}

ApplicationBase::Config&& ApplicationBase::Config::set_location(std::filesystem::path value) && {
  location = std::move(value);
  return std::move(*this);
}

ApplicationBase::ApplicationBase(Config conf)
  : config(std::move(conf))
{}

ApplicationBase::ApplicationBase(const char* name)
  : ApplicationBase(std::string(name))
{}

ApplicationBase::ApplicationBase(std::string name)
  : ApplicationBase(Config{}
    .set_name(std::move(name))
  )
{}

ApplicationBase::ApplicationBase(std::filesystem::path location)
  : ApplicationBase(Config{}
    .set_location(std::move(location))
  )
{}

ApplicationBase::ApplicationBase(std::string name, std::filesystem::path location)
  : ApplicationBase(Config{}
    .set_name(std::move(name))
    .set_location(std::move(location))
  )
{}

ApplicationBase::~ApplicationBase() = default;

void ApplicationBase::run() {}

void ApplicationBase::run(const Arguments& arguments) {
  run();
}

void ApplicationBase::run(const Arguments& arguments, const Environment& environment) {
  run(arguments);
}

void ApplicationBase::push(std::shared_ptr<Layer> layer) {
  layers_stack.emplace_back(std::move(layer));
}

}