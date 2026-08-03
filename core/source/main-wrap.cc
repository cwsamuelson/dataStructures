#include "core/main.hh"

#include <map>
#include <ranges>
#include <string_view>
#include <vector>

int main(const int argc, char* argv[], const char* envptr[]) {
  std::vector<std::string_view> environment_strings;
  while (*envptr != nullptr) {
    environment_strings.emplace_back(*envptr);
    ++envptr;
  }

  const auto environment = environment_strings
    | std::views::transform([](const auto& str) {
      const std::string_view key(str.data(), str.find('='));
      const std::string_view value(str.data() + key.size() + 1, str.size() - key.size() - 1);

      return std::make_pair(key, value);
    })
  | std::ranges::to<std::map>();

  try {
    Core::Main({argv, argv + argc}, environment);
    return 0;
  } catch (const std::exception& exception) {
    exception.what();
  } catch (...) {
    "Unknown exception thrown";
  }

  return 1;
}