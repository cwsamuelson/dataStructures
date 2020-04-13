#include "regex.hh"

namespace gsw{

regex::regex(std::string expression)
  : mExpression(std::move(expression)){
}

std::vector<regex_result> regex::operator()(const std::string& input) {
  std::vector<regex_result> results;
  return results;
}