#ifndef GALACTICSTRUCTURES_REGEX_HH
#define GALACTICSTRUCTURES_REGEX_HH

#include <vector>
#include <string>
#include <string_view>

namespace gsw {

struct regex_result{
  std::string_view view;
  size_t index;

  explicit regex_result(std::string_view vw, size_t idx)
    : view(vw)
    , index(idx)
  {}
};

//! @TODO lazy evaluation
class regex {
private:
  std::string mExpression;

  [[nodiscard]]
  bool matches(char x, char y);

public:
  explicit regex(std::string expression);

  [[nodiscard]]
  std::vector<regex_result> operator()(const std::string& input);
};

}

#endif //GALACTICSTRUCTURES_REGEX_HH
