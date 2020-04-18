#include "regex.hh"

namespace gsw{

regex::regex(std::string expression)
  : mExpression(std::move(expression)){
}

std::vector<regex_result> regex::operator()(const std::string& input) {
  std::vector<regex_result> results;

  for(size_t input_index = 0; input_index < input.size(); ++input_index){
    bool found_match = false;
    for(size_t expression_index = 0, check_index = input_index; expression_index < mExpression.size() && check_index < input.size(); ++expression_index, ++check_index){
      if(!matches(input[check_index], mExpression[expression_index])) {
        found_match = false;
        break;
      } else {
        found_match = true;
        continue;
      }
    }
    if(found_match){
      results.emplace_back(std::string_view(&input[input_index], mExpression.size()), input_index);
    }
  }

  return results;
}

bool regex::matches(char x, char y) {
  if(x == '.' || y == '.'){
    return true;
  }
  return x == y;
}

}
