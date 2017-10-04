#include<cmath>
#include<sstream>

#include<equation.hh>

using namespace std;
using namespace gsw;

double equation::variable::evaluate( const equation::data& variables ) const{
  return variables.at( name );
}

double equation::constant::evaluate( const equation::data& variables ) const{
  (void) variables;
  return value;
}

double equation::multiplication::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) * rhs->evaluate( variables );
}

double equation::division::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) / rhs->evaluate( variables );
}

double equation::addition::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) + rhs->evaluate( variables );
}

double equation::subtraction::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) - rhs->evaluate( variables );
}

double equation::inversion::evaluate( const equation::data& variables ) const{
  return -operand->evaluate( variables );
}

double equation::exponentiation::evaluate( const equation::data& variables ) const{
  return std::pow( base->evaluate( variables ), exponent->evaluate( variables ) );
}

double equation::logarithm::evaluate( const data& variables ) const{
  return std::log( value->evaluate( variables ) ) / std::log( base->evaluate( variables ) );
}

equation::equation( const equation::op_ptr value ):
  mValue( value ){
}

equation equation::operator*( const equation& multiplicand ) const{
  auto var = make_shared<equation::multiplication>();
  var->lhs = mValue;
  var->rhs = multiplicand.mValue;
  return {var};
}

equation equation::operator/( const equation& dividend ) const{
  auto var = make_shared<equation::division>();
  var->lhs = mValue;
  var->rhs = dividend.mValue;
  return {var};
}

equation equation::operator+( const equation& operand ) const{
  auto var = make_shared<equation::addition>();
  var->lhs = mValue;
  var->rhs = operand.mValue;
  return {var};
}

equation equation::operator-( const equation& operand ) const{
  auto var = make_shared<equation::subtraction>();
  var->lhs = mValue;
  var->rhs = operand.mValue;
  return {var};
}

equation equation::operator-() const{
  auto var = make_shared<equation::inversion>();
  var->operand = mValue;
  return {var};
}

equation equation::pow( const equation& operand ) const{
  auto var = make_shared<equation::exponentiation>();
  var->base = mValue;
  var->exponent = operand.mValue;
  return {var};
}

equation gsw::log( const equation& b, const equation& eq ){
  auto var = make_shared<equation::logarithm>();
  var->base = b.mValue;
  var->value = eq.mValue;
  return {var};
}

equation equation::derive( unsigned long long order ) const{
}

equation equation::integrate( unsigned long long min, unsigned long long max ) const{
}

double equation::evaluate( const equation::data& variables ) const{
  return mValue->evaluate( variables );
}

set<equation::data> equation::solve( const equation::data& variables ) const{
}

equation gsw::operator""_evar( const char* name, size_t sz ){
  string str_name( name, sz );
  stringstream ss( str_name );
  double val;

  if( ss >> val ){
    auto var = make_shared<equation::constant>();
    var->value = val;
    return {var};
  } else {
    auto var = make_shared<equation::variable>();
    var->name = str_name;
    return {var};
  }
}

