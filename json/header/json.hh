#ifndef __JSON_HH__
#define __JSON_HH__

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <variant>

namespace gsw {

template<template<typename, typename...> typename OBJECT = std::map,
         template<typename...> typename ARRAY = std::vector,
         typename STRING = std::string,
         typename INTEGER = signed long long,
         typename UINTEGER = unsigned long long,
         typename FLOAT = double,
         typename BOOL = bool>
class basic_json {
private:
  using string_t = STRING;
  using object_t = OBJECT<string_t, basic_json>;
  using array_t = ARRAY<basic_json>;
  using integer_t = INTEGER;
  using u_integer_t = UINTEGER;
  using float_t = FLOAT;
  using bool_t = BOOL;
  enum class type_tag { none, object, array, string, integer, u_integer, floating, boolean };

  type_tag mTypeTag;
  std::variant<integer_t, u_integer_t, float_t, bool_t, string_t, array_t, object_t> mData;

public:
  basic_json()
    : mTypeTag(type_tag::none){
  }
  basic_json(const basic_json&) = default;
  basic_json(basic_json&&) noexcept = default;

  basic_json& operator=(const basic_json&) = default;
  basic_json& operator=(basic_json&&) noexcept = default;

  ~basic_json() = default;

  explicit
  basic_json(object_t o)
    :mTypeTag(type_tag::object)
    , mData(std::move(o)){
  }

  explicit
  basic_json(array_t a)
    : mTypeTag(type_tag::array)
    , mData(std::move(a)){
  }

  explicit
  basic_json(string_t s)
    : mTypeTag(type_tag::string)
    , mData(std::move(s)){
  }

  explicit
  basic_json(integer_t i)
    : mTypeTag(type_tag::integer)
    , mData(std::move(i)){
  }

  explicit
  basic_json(u_integer_t u)
    : mTypeTag(type_tag::u_integer)
      , mData(std::move(u)){
  }

  explicit
  basic_json(float_t f)
    : mTypeTag(type_tag::floating)
        , mData(std::move(f)){
  }

  explicit
  basic_json(bool_t b)
    : mTypeTag(type_tag::boolean)
          , mData(std::move(b)){
  }

  //enum class type_tag { none, object, array, string, integer, u_integer, floating, boolean };
  [[nodiscard]]
  bool is_object() const{
    return mTypeTag == type_tag::object;
  }

  [[nodiscard]]
  bool is_array() const{
    return mTypeTag == type_tag::array;
  }

  [[nodiscard]]
  bool is_string() const{
    return mTypeTag == type_tag::string;
  }

  [[nodiscard]]
  bool is_integer() const{
    return mTypeTag == type_tag::integer || mTypeTag == type_tag::u_integer;
  }

  [[nodiscard]]
  bool is_signed() const{
    return mTypeTag == type_tag::integer;
  }

  [[nodiscard]]
  bool is_unsigned() const{
    return mTypeTag == type_tag::u_integer;
  }

  [[nodiscard]]
  bool is_floating() const{
    return mTypeTag == type_tag::floating;
  }

  [[nodiscard]]
  bool is_bool() const{
    return mTypeTag == type_tag::boolean;
  }
};

using json = basic_json<>;

}

#endif

