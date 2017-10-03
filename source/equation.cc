#include<equation.hh>

double variable::evaluate( const data& variables ) const{
  return variables.at( name );
}

double multiplication::evaluate( const data& variables ) const{
  return lhs->evaluate( variables ) * rhs->evaluate( variables );
}

double division::evaluate( const data& variables ) const{
  return lhs->evaluate( variables ) / rhs->evaluate( variables );
}

double addition::evaluate( const data& variables ) const{
  return lhs->evaluate( variables ) + rhs->evaluate( variables );
}

double subtraction::evaluate( const data& variables ) const{
  return lhs->evaluate( variables ) - rhs->evaluate( variables );
}

double inversion::evaluate( const data& variables ) const{
  return -operand->evaluate( variables );
}

equation equation::operator*( const equation
  auto var = make_shared<proposition::multip
  var->lhs = mValue;
  var->rhs = multiplicand;
  return {var};
}

equation equation::operator/( const equation& dividend ) const{
  auto var = make_shared<proposition::division>();
  var->lhs = mValue;
  var->rhs = dividend;
  return {var};
}

equation equation::operator+( const equation& operand ) const{
  auto var = make_shared<proposition::addition>();
  var->lhs = mValue;
  var->rhs = operand;
  return {var};
}

equation equation::operator-( const equation& operand ) const{
  auto var = make_shared<proposition::subtraction>();
  var->lhs = mValue;
  var->rhs = operand;
  return {var};
}

equation equation::operator-() const{
  auto var = make_shared<proposition::inversion>();
  var->operand = mValue;
  return {var};
}

equation equation::pow( const equation& operand ) const{
}

equation equation::derive( unsigned long long order ) const{
}

equation equation::integrate( unsigned long long min, unsigned long long max ) const{
}

double evaluate( const data& variables ) const{
  return mValue->evaluate( variables );
}

std::set<data> solve( const data& variables ) const{
}

equation operator""_evar( const char* name, size_t sz ){
  auto var = std::make_shared<equation::variable>();
  var->name = std::string( name, sz );
  return {var};
}

