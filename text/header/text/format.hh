#pragma once

#include "text/string.hh"
#include "text/support.hh"

namespace flp {

template<typename Iterator, typename ...Args>
auto format_to(Iterator iterator, const char* format, Args&& ...args) {
}

template<typename Type, typename CharT = char>
struct Formatter {
  constexpr
  auto parse(FormatParseContext<CharT>& context) {
    auto iterator = context.begin();
    while (iterator != context.end() and *iterator != '}') {
      switch (*iterator) {
      default:
        // throw std::format_error("invalid format specifier");
        break;
      }

      ++iterator;
    }

    if (iterator == context.end() or *iterator != '}') {
      // throw std::format_error("invalid format");
    }

    return iterator;
  }

  constexpr
  auto format(const Type& object, FormatContext& context) const {
  }
};

template<typename ...Args>
String format(const char* fmt, Args&& ...args) {
  return {};
}

} // namespace flp
