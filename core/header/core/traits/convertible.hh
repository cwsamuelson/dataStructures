#pragma once

namespace flp {

template<typename From, typename To>
concept ConvertibleTo = requires(const From& from) {
  static_cast<To>(from);
};

}
