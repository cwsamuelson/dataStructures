#pragma once

#include <filesystem>
#include <fstream>
#include <generator>
#include <string>
#include <vector>

namespace flp {

// basic
void read_file(const std::filesystem::path& file_path, std::span<std::byte> buffer);
std::vector<std::byte> read_file(const std::filesystem::path& file_path);

std::string read_text(const std::filesystem::path& file_path);
std::vector<std::byte> read_binary(const std::filesystem::path& file_path);

// a 'line' is a textual idea
std::generator<std::string> read_lines(const std::filesystem::path& file_path);
// a 'chunk' is a binary idea, but could be either
std::generator<std::vector<std::byte>> read_chunks(const std::filesystem::path& file_path, size_t chunk_size);

// `std::generator` can't take a template argument like `R(A, B, C)`, but the
// idea exists in other async libraries such as asio.  The idea is that using
// `co_await` on the handle will yield a `R`, but can (must) be called with
// arguments `a, b, c`.
// ```c++
// auto handle = generator<float(int)>(...);
// while (handle) {
//   const auto value = co_await handle(42);
//   assert(same_as<decltype(value), float>);
// }
// ```
// The above example illustrates the idea.  the handle can be `co_await` called
// like a function, taking arguments, which can be used to process/produce the
// next result.  In the context of file reading this may be number of lines to
// read, or the size in bytes of the chunk to read.  This way the chunk size can
// be different every iteration, unlike `read_chunks(path, size_t)`, which will
// always yield the same chunk size.
// std::generator<std::string(size_t)> read_chunks(const std::filesystem::path& file_path);

}
