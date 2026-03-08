#include "environment.hh"

#ifndef WIN32
// when not retrieved through arguments to main, linux provides `environ`
// variable through this header.  This is of course Linux only.
#include <unistd.h>
#endif

namespace flp {

std::map<std::string, std::string> parse_environment(char** environment) {
  std::map<std::string, std::string> values;

  for (auto** ptr = environment; *ptr != nullptr; ++ptr) {
    const std::string var_string = *ptr;
    // const auto&& [name, value] = var_string.split('=');
    // values[name] = value;
  }

  return values;
}

std::map<std::string, std::string> get_environment() {
  return parse_environment(environ);
}

} // namespace flp
