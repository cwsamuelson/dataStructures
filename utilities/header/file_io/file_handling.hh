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

std::generator<std::string> read_lines(const std::filesystem::path& file_path);
std::generator<std::string> read_chunks(const std::filesystem::path& file_path, size_t chunk_size);

// this doesn't exist in the standard, but does exist within other async
// libraries, and a useful idea. it's a generator that yields a chunk of a
// different size each iteration, that is specified by the caller.
//std::generator<std::string(size_t)> read_chunks(const std::filesystem::path& file_path);

}