#include<logic.hh>

using namespace std;
using namespace gsw;

bool prop::variable::evaluate( const set<string>& facts ) const{
  return facts.count( name );
}

bool prop::conjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) && rhs->evaluate( facts );
}

bool prop::disjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) || rhs->evaluate( facts );
}

bool prop::negation::evaluate( const set<string>& facts ) const{
  return !operand->evaluate( facts );
}

prop::prop( const op_ptr value ):
  mValue( value ){
}

prop prop::operator&&( const prop& conjunct ) const{
  auto var = make_shared<prop::conjunction>();
  var->lhs = mValue;
  var->rhs = conjunct.mValue;
  return {var};
}

prop prop::operator||( const prop& disjunct ) const{
  auto var = make_shared<prop::disjunction>();
  var->lhs = mValue;
  var->rhs = disjunct.mValue;
  return {var};
}

prop prop::operator!() const{
  auto var = make_shared<prop::negation>();
  var->operand = mValue;
  return {var};
}

prop prop::implies( const prop& consequent ) const{
  return !(*this) || consequent;
}

prop prop::iff( const prop& equivalent ) const{
  return this->implies( equivalent ) && equivalent.implies( *this );
}

bool prop::evaluate( const set<string> facts ) const{
  return mValue->evaluate( facts );
}

std::set<std::set<std::string> > prop::evaluate_all( const std::set<std::string>& variables ) const{
  set<set<string> > assignments;
  size_t max = 1 << ( variables.size() + 1 );
  
  for( size_t mask = 0; mask < max; ++mask ){
    set<string> test;
    
    size_t j = 1;
    for( auto it : variables ){
      if( j & mask ){
        test.insert( it );
      }
      j <<= 1;
    }
    
    if( evaluate( test ) ){
      assignments.insert( test );
    }
  }
  
  return assignments;
}

prop gsw::operator""_lvar( const char* name, size_t sz ){
  auto var = std::make_shared<prop::variable>();
  var->name = std::string( name, sz );
  return {var};
}

