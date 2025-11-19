#pragma once

#include <map>
#include <string>

namespace flp {

std::map<std::string, std::string> parse_environment(char** environment);

std::map<std::string, std::string> get_environment();

}
