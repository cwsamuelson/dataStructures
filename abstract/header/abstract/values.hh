#pragma once

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
