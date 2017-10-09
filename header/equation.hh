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

/*! Mathematical equation
 *
 * @todo implement operators with doubles
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
  private:
    bool use_power;

  public:
    op_ptr base;
    op_ptr exponent;

    exponentiation( bool power = false );

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
  using const_ptr = std::shared_ptr<constant>;

  /*! Constant equation
   *
   * Stores a constant pointer to be forwarded to an equation, used to
   * distinguish between when to use the power rule and exponentiation rule for
   * derivatives
   */
  class const_eq{
  private:
    const_eq( const const_ptr value );

    const_ptr mValue;

  public:
    friend const_eq operator""_cvar( const char* name, size_t sz );
    friend equation;
  };

  /*! Multiplication operator
   *
   * @param multiplicand operand equation to be multiplied with this
   *
   * @return an equation that represents the multiplication of this and multiplicand
   */
  equation operator*( const equation& multiplicand ) const;

  /*! Division operator
   *
   * @param dividend operand equation to divide this by
   *
   * @return an equation that represents the division of this by dividend
   */
  equation operator/( const equation& dividend ) const;

  /*! Addition operator
   *
   * @param dividend operand equation to divide this by
   *
   * @return an equation that represents the division of this by dividend
   */
  equation operator+( const equation& operand ) const;

  /*! Subtraction operator
   *
   * @param operand operand equation to subtract from this
   *
   * @return an equation that represents the subtraction of operand from this
   */
  equation operator-( const equation& operand ) const;

  /*! Negation operator
   *
   * @return negative of this
   */
  equation operator-() const;
  
  /*! Evaluation operator
   *
   * @param variables Set of variable name, value pairs to evaluate on
   *
   * @return This function evaluated with the given variable names and values
   *
   * Implementation provided here to assist with inlining
   */
  double operator()( const data& variables ) const{
    return evaluate( variables );
  }

  /*!
   */
  equation pow( const equation& operand ) const;

  /*!
   */
  equation pow( const const_eq& operand ) const;

  /*!
   */
  equation pow( double operand ) const;

  /*! Take the derivative of this wrt var
   *
   * @param var Variable with which to take the derivative
   *
   * @param order The number of derivatives to take (order-th derivative)
   *
   * @todo fix finding repeated derivatives of exponents
   */
  equation derive( std::string var, unsigned long long order = 1 ) const;

  /*!
   */
  equation integrate( unsigned long long min = 0, unsigned long long max = 0 ) const;

  /*! Evaluate this function
   *
   * @param variables Set of variable name, value pairs to evaluate on
   *
   * @return This function evaluated with the given variable names and values
   */
  double evaluate( const data& variables ) const;

  /*!
   */
  std::set<data> solve( const data& variables ) const;

  friend equation operator""_evar( const char* name, size_t sz );
  friend const_eq operator""_cvar( const char* name, size_t sz );
  friend equation log( const equation& b, const equation& eq );
};

/*! Equation string
 *
 * @param name Name of variable, or content of constant
 *
 * @param sz Length of name array
 *
 * @return Constant or variable equation, depending on data at name
 */
equation operator""_evar( const char* name, size_t sz );

/*! Constant value equation
 *
 * @param name Constant data value
 *
 * @param sz Length of name array
 *
 * @return Constant value wrapper
 *
 * This operator is used to distinguish between power and exponent rules in the
 * pow function within equation.  Using this operator as the argument to
 * equation::pow means the power rule will be utilized when taking the
 * derivative of the return value from pow.
 */
equation::const_eq operator""_cvar( const char* name, size_t sz );

/*! Logarithm of eq with base b
 *
 * @param b logarithm base (natural log base == e)
 *
 * @param eq Equation to take the logarithm of
 *
 * @return Equation representing log base b of eq
 */
equation log( const equation& b, const equation& eq );

const equation e_evar  = "2.718281828459"_evar;
const equation pi_evar = "3.141592653589"_evar;
const equation gr_evar = "1.61803398875"_evar;
}

#endif

