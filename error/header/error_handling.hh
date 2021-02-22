#ifndef GALACTICSTRUCTURES_ERROR_HANDLING_HH
#define GALACTICSTRUCTURES_ERROR_HANDLING_HH

#include <stdexcept>
#include <exception>
#include <string>
// this should enable support for c++ native format library, whenever it's added
#if !__cpp_lib_format
#include <fmt/core.h>
#define FMT fmt::
#else
#include <format>
#warning "Format library now supported native for your compiler, feel free to remove related macros and submit PR"
#define FMT std::
#endif
#if __cpp_lib_source_location
#include <source_location>
#endif

namespace gsw {
  
template<typename T>
struct NameTrait{ static inline const char* name = typeid(T).name(); };
#define REGISTER_NAME_TRAIT(T) template<> struct NameTrait<T> \
  { static inline const char* name = #T; };

class exception : public std::runtime_error {
private:
#if __cpp_lib_source_location
  std::source_location mLocation;
#else
  std::string mFile;
  std::string mFunction;
  size_t mLine;
#endif
  std::string mMessage;
  std::string mExpression;

#if __cpp_lib_source_location
  exception(std::source_location location, std::string message, std::string expression, std::string longMessage)
    : std::runtime_error(std::move(longMessage))
    , mLocation(location)
    , mMessage(std::move(message))
    , mExpression(std::move(expression))
  {}
#else
  exception(std::string file, std::string function, size_t line, std::string message, std::string expression, const std::string& longMessage)
    : std::runtime_error(longMessage)
    , mFile(std::move(file))
    , mFunction(std::move(function))
    , mLine(line)
    , mMessage(std::move(message))
    , mExpression(std::move(expression))
  {}
#endif

public:
#if __cpp_lib_source_location
  exception(std::string message, std::string expression, std::source_location location = std::source_location::current())
    : exception(location, std::move(message), std::move(expression),
      (message + " in function \"" + function + "\" in file \"" + file + ":" + std::to_string(line) + "\" while executing expression:\t" + expression)
  {}

  exception(std::string message, std::source_location location = std::source_location::current())
    : exception(location, std::move(message), "",
      (message + " in function \"" + location.function_name() + "\" in file \"" + location.file_name() + ":" + std::to_string(location.line()) + ":" + std::to_string(location.column()) + "\"")
  {}
#else
  exception(std::string file, std::string function, size_t line, std::string message, std::string expression)
    : exception(std::move(file), std::move(function), line, std::move(message), std::move(expression),
      (message + " in function \"" + function + "\" in file \"" + file + ":" + std::to_string(line) + "\" while executing expression:\t" + expression))
  {}

  exception(std::string file, std::string function, size_t line, std::string message)
    : exception(std::move(file), std::move(function), line, std::move(message), "",
      (message + " in function \"" + function + "\" in file \"" + file + ":" + std::to_string(line) + "\""))
  {}
#endif

  [[nodiscard]]
  auto file() const {
#if __cpp_lib_source_location
    return mLocation.file_name();
#else
    return mFile;
#endif
  }

  [[nodiscard]]
  auto function() const {
#if __cpp_lib_source_location
    return mLocation.function_name();
#else
    return mFunction;
#endif
  }

  [[nodiscard]]
  auto line() const {
#if __cpp_lib_source_location
    return mLocation.line();
#else
    return mLine;
#endif
  }

#if __cpp_lib_source_location
  [[nodiscard]]
  auto column() const{
    return mLocation.column();
  }
#endif

  [[nodiscard]]
  auto message() const {
    return mMessage;
  }

  [[nodiscard]]
  auto expression() const{
    return mExpression;
  }
};

}

#if __cpp_lib_source_location
#define GSW_EXPR_THROW(msg, expr) throw ::gsw::exception(msg, expr);
#define GSW_THROW(msg) throw ::gsw::exception(msg);
#else
#define GSW_EXPR_THROW(expr, ...) throw ::gsw::exception(__FILE__, __FUNCTION__, __LINE__, FMT format(__VA_ARGS__), expr);
#define GSW_THROW(...) throw ::gsw::exception(__FILE__, __FUNCTION__, __LINE__, FMT format(__VA_ARGS__));
#endif
#define GSW_WRAP(something) do{something;}while(false);
#define GSW_IF(cond, action) GSW_WRAP(if((cond)){action;});
#define GSW_VERIFY_AND(cond, action, ...) GSW_IF(!(cond), action; GSW_EXPR_THROW(#cond, __VA_ARGS__);)
#define GSW_VERIFY(cond, ...) GSW_VERIFY_AND(cond, , __VA_ARGS__);
#define GSW_CHECK_AND(cond, action, ...) GSW_IF(!(cond), action; return false;)
#define GSW_CHECK(cond, ...) GSW_CHECK_AND(cond, , __VA_ARGS__);

#endif //GALACTICSTRUCTURES_ERROR_HANDLING_HH
