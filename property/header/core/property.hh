#pragma once

#include <boost/signals2/signal.hpp>

namespace flp {

template<typename Type>
struct Property {
  Property(Property& other)
    : value(other.value) {
    other.signal.connect([this](const Type& new_value) {
      slot(new_value);
    });
  }

  Property() = default;
  Property(const Type& initial_value)
    : value(initial_value)
  {}
  Property(Type&& initial_value)
    : value(std::move(initial_value))
  {}

  template<typename ...Args>
  Property(Args&& ...args)
    : value(std::forward<Args>(args)...)
  {}

  Property& operator=(const Type& new_value) {
    value = new_value;
    signal(value);
    return *this;
  }

  Property& operator=(Type&& new_value) {
    value = std::move(new_value);
    signal(value);
    return *this;
  }

  operator const Type&() const noexcept {
    return value;
  }

  void slot(const Type& new_value) {
    value = new_value;
    signal(value);
  }

  boost::signals2::signal<void(const Type&)> signal;

private:
  Type value;
};

} // namespace flp
