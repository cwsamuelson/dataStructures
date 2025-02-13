#pragma once

#include <functional>
#include <memory>

namespace flp {

template<typename Type>
struct PolymorphicValue {
  template<std::derived_from<Type> T>
  PolymorphicValue(T&& value)
  {}

  PolymorphicValue(const PolymorphicValue& other) {
  }

  PolymorphicValue(PolymorphicValue&& other) {
  }

  PolymorphicValue& operator=(const PolymorphicValue& other) {
  }

  PolymorphicValue& operator=(PolymorphicValue&& other) {
  }

  template<std::derived_from<Type> T>
  PolymorphicValue& operator=(T&& value) {
    copy = [this] {
    };

    return *this;
  }

  ~PolymorphicValue() = default;

  Type& operator*() {
    return *value;
  }

  const Type& operator*() const {
    return *value;
  }

  Type* operator->() {
    return value.get();
  }

  const Type* operator*() const {
    return value.get();
  }

private:
  std::functional<void()> copy;
  std::unique_ptr<Type> value;
};

} // namespace flp

