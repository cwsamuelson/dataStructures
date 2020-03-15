#ifndef GALACTICSTRUCTURES_ERRORS_HH
#define GALACTICSTRUCTURES_ERRORS_HH

#include <exception>
#include <string>

namespace gsw {

class exception : public std::runtime_error {
private:
  std::string mFile;
  std::string mFunction;
  size_t mLine;
  std::string mMessage;

public:
  exception(std::string file, std::string function, size_t line, std::string message)
          : std::runtime_error(
          message + " on line: " + std::to_string(line) + " in function " + function + " and file " + file)
          , mFile(std::move(file))
          , mFunction(std::move(function))
          , mLine(line)
          , mMessage(std::move(message)) {
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
};

#define GSW_WRAP(something) do{something;}while(false);
#define GSW_IF(cond, action) GSW_WRAP(if((cond)){action;});
#define GSW_THROW(cond, msg) GSW_IF(!(cond), throw gsw::exception(__FILE__, __FUNCTION__, __LINE__, msg); );

}

#endif //GALACTICSTRUCTURES_ERRORS_HH
