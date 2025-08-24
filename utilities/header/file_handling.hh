#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace flp {
std::string read_file(const std::filesystem::path& file_path) {
  std::string result;
  std::ifstream input(file_path, std::ios::binary);
  VERIFY(input, "Could not open file({})", file_path.string());

  input.seekg(0, std::ios::end);
  result.resize(input.tellg());
  input.seekg(0, std::ios::beg);
  input.read(result.data(), result.size());

  return result;
}

}