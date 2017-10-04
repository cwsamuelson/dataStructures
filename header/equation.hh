#ifndef __EQUATION_HH__
#define __EQUATION_HH__

/*!
 * @example test-equation.cc
 */

#include<set>
#include<memory>
#include<map>
#include<string>

namespace gsw{

class equation;

equation operator""_evar( const char* name, size_t sz );
equation log( const equation& b, const equation& eq );

/*! Mathematical equation
 */
class equation{
public:
  using data = std::map<std::string, double>;

private:
  struct operation{
    virtual double evaluate( const data& variables ) const = 0;
    virtual equation derive( std::string var ) const = 0;
  };

  using op_ptr = std::shared_ptr<operation>;

  struct constant : public operation{
    double value;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct variable : public operation{
    std::string name;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct multiplication : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct division : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct addition : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct subtraction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct inversion : public operation{
    op_ptr operand;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct exponentiation : public operation{
    op_ptr base;
    op_ptr exponent;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };
  struct logarithm : public operation{
    op_ptr base;
    op_ptr value;

    double evaluate( const data& variables ) const;
    equation derive( std::string var ) const;
  };

  equation( const op_ptr value );

  op_ptr mValue;

public:
  /*!
   */
  equation operator*( const equation& multiplicand ) const;

  /*!
   */
  equation operator/( const equation& dividend ) const;

  /*!
   */
  equation operator+( const equation& operand ) const;

  /*!
   */
  equation operator-( const equation& operand ) const;

  /*!
   */
  equation operator-() const;
  
  /*!
   */
  double operator()( const data& variables ) const;

  /*!
   */
  equation pow( const equation& operand ) const;

  /*!
   */
  equation derive( std::string var, unsigned long long order = 1 ) const;

  /*!
   */
  equation integrate( unsigned long long min = 0, unsigned long long max = 0 ) const;

  /*!
   */
  double evaluate( const data& variables ) const;

  /*!
   */
  std::set<data> solve( const data& variables ) const;

  /*!
   */
  friend equation operator""_evar( const char* name, size_t sz );

  /*!
   */
  friend equation log( const equation& b, const equation& eq );
};

const equation e_evar = "2.718281828459"_evar;
const equation pi_evar = "3.141592"_evar;
}

#endif

