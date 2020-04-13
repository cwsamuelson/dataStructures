#include "regex.hh"

namespace gsw{

regex::regex(std::string expression)
  : mExpression(std::move(expression)){
}

std::vector<regex_result> regex::operator()(const std::string& input) {
  std::vector<regex_result> results;

  for(size_t input_index = 0; input_index < input.size(); ++input_index){
    for(size_t expression_index = 0; expression_index < mExpression.size(); ++expression_index){
      if(!matches(input[input_index], mExpression[expression_index])) {
        continue;
      } else {

      }
    }
  }

  return results;
}

bool regex::matches(char x, char y) {
  return x == y;
}

}
