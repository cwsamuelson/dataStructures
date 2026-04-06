#include "core/application.hh"
#include "core/main.hh"

#include <filesystem>
#include <string>

std::shared_ptr<Core::ApplicationBase> Core::get_application() {
  return nullptr;
}

std::shared_ptr<Core::Layer> Core::get_app_layer() {
  return nullptr;
}

namespace Core {

void Main(const Arguments& arguments, const Environment& environment) {
  // Get name from how it's called
  const std::string name = std::filesystem::path(arguments.front()).filename().string();
  // Get executable path from canonical file path
  const std::filesystem::path exe_path = std::filesystem::canonical(arguments.front());
  // Initial working directory
  const std::filesystem::path working_path = std::filesystem::current_path();

  // spdlog_setup::from_file("log_conf.toml");

  const auto application_pointer = get_application();
  ApplicationBase& application = *application_pointer;

  application.push(get_app_layer());
  application.run(arguments, environment);
}

}
