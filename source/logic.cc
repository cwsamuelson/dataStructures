#include<cmath>

#include<logic.hh>

using namespace std;
using namespace gsw;

bool proposition::variable::evaluate( const set<string>& facts ) const{
  return facts.count( name );
}

bool proposition::conjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) && rhs->evaluate( facts );
}

bool proposition::disjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) || rhs->evaluate( facts );
}

bool proposition::exDisjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) ^ rhs->evaluate( facts );
}

bool proposition::negation::evaluate( const set<string>& facts ) const{
  return !operand->evaluate( facts );
}

proposition::proposition( const op_ptr value ):
  mValue( value ){
}

proposition proposition::operator&&( const proposition& conjunct ) const{
  auto var = make_shared<proposition::conjunction>();
  var->lhs = mValue;
  var->rhs = conjunct.mValue;
  return {var};
}

proposition proposition::operator||( const proposition& disjunct ) const{
  auto var = make_shared<proposition::disjunction>();
  var->lhs = mValue;
  var->rhs = disjunct.mValue;
  return {var};
}

proposition proposition::operator^( const proposition& operand ) const{
  auto var = make_shared<proposition::exDisjunction>();
  var->lhs = mValue;
  var->rhs = operand.mValue;
  return {var};
}

proposition proposition::operator!() const{
  auto var = make_shared<proposition::negation>();
  var->operand = mValue;
  return {var};
}

proposition proposition::implies( const proposition& consequent ) const{
  return !(*this) || consequent;
}

proposition proposition::iff( const proposition& equivalent ) const{
  return this->implies( equivalent ) && equivalent.implies( *this );
}

bool proposition::evaluate( const set<string> facts ) const{
  return mValue->evaluate( facts );
}

set<set<string> > proposition::evaluate_all( const set<string>& variables ) const{
  set<set<string> > assignments;
  size_t max = pow( 2, variables.size() );

  // mask used to describe which elements from variables should be tested
  // and is then incremented to retrieve the next 'permutation'
  for( size_t mask = 0; mask < max; ++mask ){
    set<string> test;

    // each element of variables is mapped to a bit in mask
    // each bit is tested, and each element of variables is added appropriately
    size_t j = 1;
    for( auto it : variables ){
      if( j & mask ){
        test.insert( it );
      }
      j <<= 1;
    }

    // once a set of values from variables is generated, test it
    if( evaluate( test ) ){
      assignments.insert( test );
    }
  }

  return assignments;
}

proposition gsw::operator""_lvar( const char* name, size_t sz ){
  auto var = std::make_shared<proposition::variable>();
  var->name = std::string( name, sz );
  return {var};
}

