#include "regex.hh"

#include <cctype>

namespace gsw {

token::token(char tok, token_category cat)
  : mCategory(cat)
  , mToken(tok)
{
  if(cat == token_category::match){
    if(mToken == '.'){
      mCategory = token_category::any;
    } else if(mToken == 'd'){
      mCategory = token_category::number;
    }
  }
}

token_category token::category() const{
  return mCategory;
}

char token::tok() const{
  return mToken;
}

bool token::matches(char target){
  return true;
}

bool token::matches_literal(char x, char y) {
  return x == y;
}

bool token::matches_any(char) {
  return true;
}

bool token::matches_whitespace(char w) {
  return std::isspace(w);
}

bool token::matches_number(char d){
  return std::isdigit(d);
}

[[nodiscard]]
static bool matches(token tok, char c) {
  switch(tok.category()){
  case token_category::literal:
    return tok.matches_literal(tok.tok(), c);
  case token_category::whitespace:
    return tok.matches_whitespace(c);
  case token_category::number:
    return tok.matches_number(c);
  case token_category::any:
    return tok.matches_any(c);
  default:
    break;
    //error?
  }
}

regex::regex(std::string expression)
  : mExpression(std::move(expression)) {
  for(size_t i = 0; i < mExpression.size(); ++i){
    if(mExpression[i] == '\\'){
      ++i;
      //special
      switch(mExpression[i]){
      case 'd':
        mTokens.emplace_back('d', token_category::number);
        break;
      case 'w':
        mTokens.emplace_back('w', token_category::whitespace);
        break;
      }
    } else if(mExpression[i] == '.') {
      mTokens.emplace_back(mExpression[i], token_category::any);
    } else {
      mTokens.emplace_back(mExpression[i], token_category::literal);
    }
  }
}

std::vector<regex_result> regex::operator()(const std::string& input) {
  std::vector<regex_result> results;

  for(size_t input_index = 0; input_index < input.size(); ++input_index) {
    bool found_match = false;
    for(size_t token_index = 0, check_index = input_index;
        token_index < mTokens.size() && check_index < input.size();
        ++token_index, ++check_index) {
      if(!matches(mTokens[token_index], input[check_index])) {
        found_match = false;
        break;
      } else {
        found_match = true;
        continue;
      }
    }

    if(found_match) {
      results.emplace_back(std::string_view(&input[input_index], mExpression.size()), input_index);
    }
  }

  return results;
}

}
