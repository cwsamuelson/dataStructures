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

namespace {

enum class token_category {
  literal, match,

  any, whitespace, number,
};

class token {
private:
  token_category mCategory;
  char mToken;

public:
  explicit token(char tok, token_category cat = token_category::literal);

  [[nodiscard]]
  token_category category() const;

  [[nodiscard]]
  char tok() const;

  [[nodiscard]]
  bool matches(char target);

  [[nodiscard]]
  static bool matches_literal(char x, char y);

  [[nodiscard]]
  static bool matches_any(char);

  [[nodiscard]]
  static bool matches_whitespace(char w);

  [[nodiscard]]
  static bool matches_number(char d);
};

}

//! @TODO lazy evaluation
// currently returning the whole list of expressions, should at least provide
// the option of only getting results as they're found.  faster if not all are
// desired
class regex {
private:
  std::string mExpression;
  std::vector<token> mTokens;

public:
  explicit regex(std::string expression);

  [[nodiscard]]
  std::vector<regex_result> operator()(const std::string& input);
};

}

#endif //GALACTICSTRUCTURES_REGEX_HH
