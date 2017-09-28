#ifndef __LOGIC_HH__
#define __LOGIC_HH__

#include<string>
#include<set>
#include<memory>

namespace gsw{

class prop;

prop operator""_lvar( const char* name, size_t sz );

class prop{
private:
  struct operation{
    virtual bool evaluate( const std::set<std::string>& facts ) const = 0;
  };

  using op_ptr = std::shared_ptr<operation>;

  struct variable : public operation{
    std::string name;

    bool evaluate( const std::set<std::string>& facts ) const;
  };
  struct conjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const std::set<std::string>& facts ) const;
  };
  struct disjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const std::set<std::string>& facts ) const;
  };
  struct negation : public operation{
    op_ptr operand;

    bool evaluate( const std::set<std::string>& facts ) const;
  };

  prop( const op_ptr value );

  op_ptr mValue;

public:
  prop operator&&( const prop& conjunct ) const;

  prop operator||( const prop& disjunct ) const;

  prop operator!() const;

  prop implies( const prop& consequent ) const;

  prop iff( const prop& consequent ) const;

  bool evaluate( const std::set<std::string> facts ) const;
  
  //std::set<std::set<std::string> > evaluate_all( const std::set<std::string>& variables ) const;

  friend prop operator""_lvar( const char* name, size_t sz );
};

}

#endif

