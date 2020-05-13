#ifndef GALACTICSTRUCTURES_ERROR_HANDLING_HH
#define GALACTICSTRUCTURES_ERROR_HANDLING_HH

#include <exception>
#include <string>

namespace gsw {

class exception : public std::runtime_error {
private:
  std::string mFile;
  std::string mFunction;
  size_t mLine;
  std::string mMessage;
  std::string mExpression;

public:
  exception(std::string file, std::string function, size_t line, std::string message, std::string expression)
          : std::runtime_error(
          message + " on line: " + std::to_string(line) + " in function " + function + " and file " + file + " while executing expression:" + expression)
          , mFile(std::move(file))
          , mFunction(std::move(function))
          , mLine(line)
          , mMessage(std::move(message))
          , mExpression(std::move(expression)){
  }

  [[nodiscard]]
  auto file() const {
    return mFile;
  }

  [[nodiscard]]
  auto function() const {
    return mFunction;
  }

  [[nodiscard]]
  auto line() const {
    return mLine;
  }

  [[nodiscard]]
  auto message() const {
    return mMessage;
  }

  [[nodiscard]]
  auto expression() const{
    return mExpression;
  }
};

#define GSW_THROW(msg, expr) throw ::gsw::exception(__FILE__, __FUNCTION__, __LINE__, msg, expr);
#define GSW_WRAP(something) do{something;}while(false);
#define GSW_IF(cond, action) GSW_WRAP(if((cond)){action;});
#define GSW_VERIFY_AND(cond, action, msg) GSW_IF(!(cond), action; GSW_THROW(msg, #cond);)
#define GSW_VERIFY(cond, msg) GSW_VERIFY_AND(cond, , msg);
#define GSW_CHECK_AND(cond, action, msg) GSW_IF(!(cond), action; return false;)
#define GSW_CHECK(cond, msg) GSW_CHECK_AND(cond, , msg);

}

#endif //GALACTICSTRUCTURES_ERROR_HANDLING_HH
