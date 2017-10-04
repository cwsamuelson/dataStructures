#include<cmath>
#include<sstream>

#include<equation.hh>

using namespace std;
using namespace gsw;

double equation::variable::evaluate( const equation::data& variables ) const{
  return variables.at( name );
}

equation equation::variable::derive( std::string var ) const{
  auto cnstnt = make_shared<equation::constant>();

  if( var == name ){
    cnstnt->value = 1;
  } else {
    cnstnt->value = 0;
  }

  return {cnstnt};
}

double equation::constant::evaluate( const equation::data& variables ) const{
  (void) variables;
  return value;
}

equation equation::constant::derive( std::string var ) const{
  (void) var;
  auto ptr = make_shared<equation::constant>();
  ptr->value = 0;
  return {ptr};
}

double equation::multiplication::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) * rhs->evaluate( variables );
}

equation equation::multiplication::derive( std::string var ) const{
  return ( equation( lhs ) * rhs->derive( var ) ) + ( equation( rhs ) * lhs->derive( var ) );
}

double equation::division::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) / rhs->evaluate( variables );
}

equation equation::division::derive( std::string var ) const{
  return ( ( lhs->derive( var ) * rhs ) - ( equation( rhs ) * lhs->derive( var ) ) ) / ( equation( rhs ) * equation( rhs ) );
}

double equation::addition::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) + rhs->evaluate( variables );
}

equation equation::addition::derive( std::string var ) const{
  return lhs->derive( var ) + rhs->derive( var );
}

double equation::subtraction::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) - rhs->evaluate( variables );
}

equation equation::subtraction::derive( std::string var ) const{
  return lhs->derive( var ) - rhs->derive( var );
}

double equation::inversion::evaluate( const equation::data& variables ) const{
  return -operand->evaluate( variables );
}

equation equation::inversion::derive( std::string var ) const{
  return -equation( operand->derive( var ) );
}

double equation::exponentiation::evaluate( const equation::data& variables ) const{
  return std::pow( base->evaluate( variables ), exponent->evaluate( variables ) );
}

/*! @todo distinguish between using power rule and exponentiation rule */
equation equation::exponentiation::derive( std::string var ) const{
  auto original = make_shared<equation::exponentiation>();
  original->exponent = exponent;
  original->base = base;
  return exponent->derive( var ) * equation( original ) * gsw::log( gsw::e_evar, {base} );
}

double equation::logarithm::evaluate( const data& variables ) const{
  return std::log( value->evaluate( variables ) ) / std::log( base->evaluate( variables ) );
}

equation equation::logarithm::derive( std::string var ) const{
  return "1"_evar / ( equation( value ) * gsw::log( gsw::e_evar, {base} ) );
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

double equation::operator()( const data& variables ) const{
  return evaluate( variables );
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

equation equation::derive( std::string var, unsigned long long order ) const{
//  while( order-- ){
    return mValue->derive( var );
//  }
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

