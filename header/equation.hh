#ifndef __EQUATION_HH__
#define __EQUATION_HH__

/*!
 * @example test-equation.cc
 */

#include<set>

namespace gsw{

class equation;

equation operator""_lvar( const char* name, size_t sz );

/*! Mathematical equation
 */
class equation{
public:
  using data = std::set<std::tuple<std::string, double> >;

private:
  struct operation{
    virtual bool evaluate( const data& variables ) const = 0;
  };

  using op_ptr = std::shared_ptr<operation>;

  struct variable : public operation{
    bool evaluate( const data& variables ) const;
  };
  struct multiplication : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const data& variables ) const;
  };
  struct division : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const data& variables ) const;
  };
  struct addition : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const data& variables ) const;
  };
  struct subtraction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const data& variables ) const;
  };
  struct inversion : public operation{
    op_ptr operand;

    bool evaluate( const data& variables ) const;
  };

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
};

}

#endif

