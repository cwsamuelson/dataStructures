#include "file_io/file_handling.hh"

#include <error_help.hh>

#include <span>
#include <vector>

namespace flp {

void read_file(const std::filesystem::path& file_path, const std::span<std::byte> buffer) {
  std::ifstream input(file_path, std::ios::binary | std::ios::ate);
  VERIFY(input, "Could not open file({})", file_path.string());

  VERIFY(buffer.size_bytes() >= input.tellg(), "Buffer is too small for file({})", file_path.string());
  input.seekg(0, std::ios::beg);
  input.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
}

std::vector<std::byte> read_file(const std::filesystem::path& file_path) {
  std::vector<std::byte> buffer;
  VERIFY(exists(file_path), "File({}) does not exist", file_path.string());
  buffer.resize(file_size(file_path));
  read_file(file_path, buffer);

  return buffer;
}

std::string read_text(const std::filesystem::path& file_path) {
  auto buffer = read_file(file_path);
  return { reinterpret_cast<char*>(buffer.data()), buffer.size() };
}

std::vector<std::byte> read_binary(const std::filesystem::path& file_path) {
  return read_file(file_path);
}

std::generator<std::string> read_lines(const std::filesystem::path& file_path) {
  std::ifstream input(file_path, std::ios::binary);
  VERIFY(input, "Could not open file({})", file_path.string());

  for (std::string line; std::getline(input, line);) {
    co_yield line;
  }

  // co_return total_lines_read;
}

std::generator<std::vector<std::byte>> read_chunks(const std::filesystem::path& file_path, const size_t chunk_size) {
  std::ifstream input(file_path);
  VERIFY(input, "Could not open file({})", file_path.string());

  std::vector<std::byte> chunk;
  chunk.resize(chunk_size);
  for (; input.read(reinterpret_cast<char*>(chunk.data()), chunk_size);) {
    co_yield chunk;
  }

  // co_return total_chunks_read;
}

// This is an approximated implementation.  I highly suspect it won't quite work correctly.
// std::generator<std::string(size_t)> read_chunks(const std::filesystem::path& file_path) {
//   std::ifstream input(file_path);
//   VERIFY(input, "Could not open file({})", file_path.string());
// 
//   size_t chunk_size = co_await co_yield "";
// 
//   for (std::string chunk; input.read(chunk.data(), chunk_size);) {
//     chunk_size = co_await co_yield chunk;
//   }
// }

} // namespace flp
