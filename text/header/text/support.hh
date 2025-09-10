#pragma once

#include <cstddef>

namespace flp {

[[nodiscard]]
size_t strlen(const char* cstring) noexcept;

template<typename CharT>
struct FormatParseContext {
  struct Iterator {
    CharT c{};

    [[nodiscard]]
    decltype(auto) operator*(this auto&& self) noexcept {
      return self.c;
    }

    [[nodiscard]]
    friend auto operator<=>(const Iterator&, const Iterator&) noexcept = default;
  };

  Iterator begin() {
    return {};
  }

  Iterator end() {
    return {};
  }
};

template<typename CharT>
struct FormatContext {
};

}
