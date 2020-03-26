#ifndef __JSON_HH__
#define __JSON_HH__

#include <type_traits>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <variant>

namespace gsw {

template<template<typename, typename...> typename OBJECT = std::map,
        template<typename...>
                                         typename ARRAY = std::vector,
                                         typename STRING = std::string,
                                         typename INTEGER = signed long long,
                                         typename UINTEGER = unsigned long long,
                                         typename FLOAT = double,
                                         typename BOOL = bool>
class basic_json {
private:
  using string_t = STRING;
  template<typename T>
  using object_t = OBJECT<string_t, T>;
  template<typename T>
  using array_t = ARRAY<T>;
  using integer_t = INTEGER;
  using u_integer_t = UINTEGER;
  using float_t = FLOAT;
  using bool_t = BOOL;
  enum class type_tag { none, object, array, string, integer, u_integer, floating, boolean };

  type_tag mTypeTag;
  std::variant<integer_t, u_integer_t, float_t, bool_t, string_t, array_t<basic_json>, object_t<basic_json>> mData;

public:
  basic_json()
          : mTypeTag(type_tag::none) {
  }
  basic_json(const basic_json&) = default;
  basic_json(basic_json&&) noexcept = default;

  basic_json& operator=(const basic_json&) = default;
  basic_json& operator=(basic_json&&) noexcept = default;

  ~basic_json() = default;

  template<typename T>
  basic_json(std::initializer_list<T> il){
  }

  template<typename T>
  explicit basic_json(const object_t<T>& o)
          : mTypeTag(type_tag::object) {
    object_t<basic_json> m;

    for(const auto&[key, value] : o) {
      m[key] = basic_json(value);
    }

    mData = std::move(m);
  }

  template<typename T>
  explicit basic_json(const array_t<T>& a)
          : mTypeTag(type_tag::array) {
    array_t<basic_json> v;

    for(const auto& element : a) {
      v.emplace_back(element);
    }

    mData = std::move(v);
  }

  explicit basic_json(string_t s)
          : mTypeTag(type_tag::string)
          , mData(std::move(s)) {
  }

  explicit basic_json(const char* arr)
          : mTypeTag(type_tag::string)
          , mData(arr) {
  }

  template<typename INT, std::enable_if_t<std::is_integral<INT>::value && std::is_signed<INT>::value, int> = 0>
  explicit basic_json(INT i)
          : mTypeTag(type_tag::integer)
          , mData(integer_t(i)) {
  }

  template<typename UINT, std::enable_if_t<std::is_integral<UINT>::value && !std::is_signed<UINT>::value, int> = 0>
  explicit basic_json(UINT u)
          : mTypeTag(type_tag::u_integer)
          , mData(u_integer_t(u)) {
  }

  template<typename FLT, std::enable_if_t<std::is_floating_point<FLT>::value, int> = 0>
  explicit basic_json(FLT f)
          : mTypeTag(type_tag::floating)
          , mData(float_t(f)) {
  }

  explicit basic_json(bool_t b)
          : mTypeTag(type_tag::boolean)
          , mData(b) {
  }

  //templatize some of the constructors and assignment operators?

  template<typename T>
  basic_json& operator=(object_t<T> o) {
    mTypeTag = type_tag::object;
    object_t<basic_json> m;

    for(const auto&[key, value] : o) {
      m[key] = basic_json(value);
    }

    mData = std::move(m);

    return *this;
  }

  template<typename T>
  basic_json& operator=(array_t<T> a) {
    mTypeTag = type_tag::array;
    array_t<basic_json> v;

    for(const auto& element : a) {
      v.emplace_back(element);
    }

    mData = std::move(v);

    return *this;
  }

  basic_json& operator=(string_t s) {
    mTypeTag = type_tag::string;
    mData = std::move(s);

    return *this;
  }

  basic_json& operator=(const char* arr) {
    mTypeTag = type_tag::string;
    mData = string_t(arr);

    return *this;
  }

  template<typename INT, std::enable_if_t<std::is_integral<INT>::value && std::is_signed<INT>::value, int> = 0>
  basic_json& operator=(INT i) {
    mTypeTag = type_tag::integer;
    mData = integer_t(i);

    return *this;
  }

  template<typename UINT, std::enable_if_t<std::is_integral<UINT>::value && !std::is_signed<UINT>::value, int> = 0>
  basic_json& operator=(UINT u) {
    mTypeTag = type_tag::u_integer;
    mData = u_integer_t(u);

    return *this;
  }

  template<typename FLT, std::enable_if_t<std::is_floating_point<FLT>::value, int> = 0>
  basic_json& operator=(FLT f) {
    mTypeTag = type_tag::floating;
    mData = float_t(f);

    return *this;
  }

  basic_json& operator=(bool_t b) {
    mTypeTag = type_tag::boolean;
    mData = std::move(b);

    return *this;
  }

  [[nodiscard]]
  bool is_object() const {
    return mTypeTag == type_tag::object;
  }

  [[nodiscard]]
  bool is_array() const {
    return mTypeTag == type_tag::array;
  }

  [[nodiscard]]
  bool is_string() const {
    return mTypeTag == type_tag::string;
  }

  [[nodiscard]]
  bool is_number() const{
    return mTypeTag == type_tag::integer || mTypeTag == type_tag::u_integer || mTypeTag == type_tag::floating;
  }

  [[nodiscard]]
  bool is_integer() const {
    return mTypeTag == type_tag::integer || mTypeTag == type_tag::u_integer;
  }

  [[nodiscard]]
  bool is_signed() const {
    return mTypeTag == type_tag::integer || mTypeTag == type_tag::floating;
  }

  [[nodiscard]]
  bool is_unsigned() const {
    return mTypeTag == type_tag::u_integer;
  }

  [[nodiscard]]
  bool is_floating() const {
    return mTypeTag == type_tag::floating;
  }

  [[nodiscard]]
  bool is_bool() const {
    return mTypeTag == type_tag::boolean;
  }
};

using json = basic_json<>;

}

#endif

