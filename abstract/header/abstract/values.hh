#pragma once

#include <concepts>
#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace flp::Abstract {

template<
  template<typename, typename, typename...> typename MapType = std::map,
  template<typename, typename...> typename ArrayType = std::vector,
  typename StringType = std::string,
  typename BooleanType = bool,
  typename SignedIntegerType = int64_t,
  typename UnsignedIntegerType = uint64_t,
  typename FloatType = double,
  typename BinaryType = ArrayType<std::byte>,
  template<typename> typename AllocatorType = std::allocator
>
struct Value {
  using String = StringType;
  using Map = MapType<String, Value>;
  using Array = ArrayType<Value>;
  using Boolean = BooleanType;
  using SignedInteger = SignedIntegerType;
  using UnsignedInteger = UnsignedIntegerType;
  using Float = FloatType;
  using Binary = BinaryType;

  template<typename Type>
  using Allocator = AllocatorType<Type>;

  Value() = default;

  Value(std::nullptr_t)
    : Value()
  {}

  template<typename Type>
  Value(Type object)
    : value(std::move(object))
  {}

  Value& operator=(std::nullptr_t) {
    value = {};
    return *this;
  }

  template<typename Type>
  Value& operator=(Type object) {
    value = std::move(object);
    return *this;
  }

  // Value& operator=(const Boolean object) {
  //   value = object;
  //   return *this;
  // }

  // template<std::signed_integral SInt>
  //   requires (not std::same_as<SInt, Boolean>)
  // Value& operator=(const SInt& sivalue) {
  //   value = static_cast<SignedInteger>(sivalue);
  //   return *this;
  // }

  // template<std::unsigned_integral UInt>
  //   requires (not std::same_as<UInt, Boolean>)
  // Value& operator=(const UInt& uivalue) {
  //   value = static_cast<UnsignedInteger>(uivalue);
  //   return *this;
  // }

  // template<std::floating_point FloatPt>
  //   requires (
  //     not std::signed_integral<FloatPt>
  // and not std::unsigned_integral<FloatPt>)
  // Value& operator=(const FloatPt& fpvalue) {
  //   value = static_cast<Float>(fpvalue);
  //   return *this;
  // }

  // template<typename Type>
  // Value& operator=(const ArrayType<Type>& array) {
  //   Array new_value;

  //   for (const auto& element : array) {
  //     new_value.push_back(element);
  //   }

  //   value = std::move(new_value);

  //   return *this;
  // }

  std::variant<
    std::monostate,
    String,
    Map,
    Array,
    Boolean,
    SignedInteger,
    UnsignedInteger,
    Float,
    Binary
  > value;
};

}
