#pragma once

namespace flp {

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

struct FormatContext {
};

}
