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
equation log( size_t sz, const equation& eq );

/*! Mathematical equation
 */
class equation{
public:
  using data = std::map<std::string, double>;

private:
  struct operation{
    virtual double evaluate( const data& variables ) const = 0;
  };

  using op_ptr = std::shared_ptr<operation>;

  struct variable : public operation{
    std::string name;

    double evaluate( const data& variables ) const;
  };
  struct multiplication : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
  };
  struct division : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
  };
  struct addition : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
  };
  struct subtraction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    double evaluate( const data& variables ) const;
  };
  struct inversion : public operation{
    op_ptr operand;

    double evaluate( const data& variables ) const;
  };
  struct exponentiation : public operation{
    op_ptr base;
    op_ptr exponent;

    double evaluate( const data& variables ) const;
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
  equation pow( const equation& operand ) const;

  /*!
   */
  equation derive( unsigned long long order = 1 ) const;

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
  friend equation log( size_t sz, const equation& eq );
};

}

#endif

