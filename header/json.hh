#ifndef __JSON_HH__
#define __JSON_HH__

#include<string>
#include<vector>
#include<map>
#include<utility>
#include<variant>

// json supports int, string, array/vector, and object/map
/*!
 */
class json{
  using object_t = std::map<std::string, json>;
  using array_t = std::vector<json>;
  using string_t = std::string;
  using integer_t = signed long long;
  using u_integer_t = unsigned long long;
  using float_t = double;
  using bool_t = bool;

  std::variant<integer_t, u_integer_t, float_t, bool_t, string_t, array_t, object_t> mData;
};

#endif

