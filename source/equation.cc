#include<equation.hh>

equation equation::operator*( const equation& multiplicand ) const{
  auto var = make_shared<proposition::multiplication>();
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
}

