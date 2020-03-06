#ifndef GALACTICSTRUCTURES_ERRORS_HH
#define GALACTICSTRUCTURES_ERRORS_HH

#include <exception>
#include <string>

namespace gsw{

class exception : public std::exception{
public:
  exception(std::string file, std::string function, size_t line, std::string message){}
};

#define GSW_WRAP(anything) do{anything;}while(false);
#define GSW_THROW(cond, msg) GSW_WRAP(if(!(cond)){ throw gsw::exception(__FILE__, __FUNCTION__, __LINE__, msg); });

}

#endif //GALACTICSTRUCTURES_ERRORS_HH
