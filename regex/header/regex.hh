#ifndef GALACTICSTRUCTURES_REGEX_HH
#define GALACTICSTRUCTURES_REGEX_HH

#include <vector>
#include <string>

namespace gsw {

struct regex_result{
  std::string_view view;
  size_t index;
};

class regex {
private:
  std::string mExpression;

public:
  explicit regex(std::string expression);

  [[nodiscard]]
  std::vector<regex_result> operator()(const std::string& input);
};

}

#endif //GALACTICSTRUCTURES_REGEX_HH
