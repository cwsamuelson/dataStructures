#pragma once

#include <concepts>
#include <cstdint>

namespace flp {

namespace {

template<typename Type>
struct MakeUnsignedImpl;

template<std::unsigned_integral UInt>
struct MakeUnsignedImpl<UInt> {
  using type = UInt;
};

template<>
struct MakeUnsignedImpl<int8_t> {
  using type = uint8_t;
};

template<>
struct MakeUnsignedImpl<int16_t> {
  using type = uint16_t;
};

template<>
struct MakeUnsignedImpl<int32_t> {
  using type = uint32_t;
};

template<>
struct MakeUnsignedImpl<int64_t> {
  using type = uint64_t;
};

// ---

template<typename Type>
struct MakeSignedImpl;

template<std::signed_integral SInt>
struct MakeSignedImpl<SInt> {
  using type = SInt;
};

template<>
struct MakeSignedImpl<uint8_t> {
  using type = int8_t;
};

template<>
struct MakeSignedImpl<uint16_t> {
  using type = int16_t;
};

template<>
struct MakeSignedImpl<uint32_t> {
  using type = int32_t;
};

template<>
struct MakeSignedImpl<uint64_t> {
  using type = int64_t;
};

}

}
