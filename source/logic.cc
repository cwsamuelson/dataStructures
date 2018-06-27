#include<cmath>

#include<logic.hh>

using namespace std;
using namespace gsw;
using namespace gsw::detail;

/**************
 * operations *
 **************/
  /***********
   * helpers *
   ***********/
set<string>
invert( set<string> operand, set<string> variables ){
  for( auto op : operand ){
    if( variables.count( op ) ){
      variables.erase( variables.find( op ) );
    }
  }

  return variables;
}

  /************
   * variable *
   ************/
bool
proposition::variable::evaluate( const set<string>& facts ) const{
  return facts.count( name );
}

set<set<string> >
proposition::variable::solve( set<string> data ) const{
// this throws in some confusion.  what to do if this variable doesn't exist in
//  the variables to be solved on?
  set<set<string> > assignments;
  size_t max = pow( 2, data.size() );

  // mask used to describe which elements from data should be tested
  // and is then incremented to retrieve the next 'permutation'
  for( size_t mask = 0; mask < max; ++mask ){
    set<string> test;

    // each element of data is mapped to a bit in mask
    // each bit is tested, and each respective variable is added appropriately
    size_t j = 1;
    for( auto var : data ){
      if( j & mask ){
        test.insert( var );
      }
      j <<= 1;
    }

    // once a set of values from variables is generated, add this var, and save it
    test.insert( name );
    assignments.insert( test );
  }

  return assignments;
}

  /***************
   * conjunction *
   ***************/
bool
proposition::conjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) && rhs->evaluate( facts );
}

set<set<string> >
proposition::conjunction::solve( set<string> data ) const{
  // given:
  // (X|Y)&(W|Z)
  // solve as:
  // ({X}|{Y})&({W}|{Z})
  // {{X}, {Y}, {X, Y}}&{{W}, {Z}, {W, Z}}
  // add each rhs solution to the lhs solution
  //  to generate all possible solutions
  // {{W, X}, {W, Y}, {W, X, Y},//add W to each lhs
  //  {Z, X}, {Z, Y}, {X, Y, Z}, //add Z to each lhs
  //  ...etc}
  auto lhs_data = lhs->solve( data );
  auto rhs_data = rhs->solve( data );
  set<set<string> > result;

  for( auto rhs_solution : rhs_data ){
    for( auto lhs_solution : lhs_data ){
      result.insert( merge( lhs_solution, rhs_solution ) );
    }
  }

  return result;
}

  /***************
   * disjunction *
   ***************/
bool
proposition::disjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) || rhs->evaluate( facts );
}

set<set<string> >
proposition::disjunction::solve( set<string> data ) const{
  auto lhs_data = lhs->solve( data );
  auto rhs_data = rhs->solve( data );
  set<set<string> > result;

  for( auto lhs_solution : lhs_data ){
    result.insert( lhs_solution );
    for( auto rhs_solution : rhs_data ){
      result.insert( rhs_solution );
      result.insert( merge( lhs_solution, rhs_solution ) );
    }
  }

  return result;
}

  /*************************
   * exclusive disjunction *
   *************************/
bool
proposition::exDisjunction::evaluate( const set<string>& facts ) const{
  return lhs->evaluate( facts ) ^ rhs->evaluate( facts );
}

set<set<string> >
proposition::exDisjunction::solve( set<string> data ) const{
  auto lhs_data = lhs->solve( data );
  auto rhs_data = rhs->solve( data );
  set<set<string> > result( lhs_data );

  for( auto rhs_solution : rhs_data ){
    result.insert( rhs_solution );
  }

  return result;
}

  /************
   * negation *
   ************/
bool
proposition::negation::evaluate( const set<string>& facts ) const{
  return !operand->evaluate( facts );
}

set<set<string> >
proposition::negation::solve( set<string> data ) const{
  auto solutions = operand->solve( data );
  set<set<string> > result;

  for( auto solution : solutions ){
    result.insert( invert( solution, data ) );
  }

  return result;
}

/***************
 * proposition *
 ***************/
proposition::proposition( const op_ptr value )
  : mValue( value ){
}

proposition
proposition::operator&&( const proposition& conjunct ) const{
  auto var = make_shared<proposition::conjunction>();

  var->lhs = mValue;
  var->rhs = conjunct.mValue;

  return {var};
}

proposition
proposition::operator||( const proposition& disjunct ) const{
  auto var = make_shared<proposition::disjunction>();

  var->lhs = mValue;
  var->rhs = disjunct.mValue;

  return {var};
}

proposition
proposition::operator^( const proposition& operand ) const{
  auto var = make_shared<proposition::exDisjunction>();

  var->lhs = mValue;
  var->rhs = operand.mValue;

  return {var};
}

proposition
proposition::operator!() const{
  auto var = make_shared<proposition::negation>();

  var->operand = mValue;

  return {var};
}

proposition
proposition::implies( const proposition& consequent ) const{
  return !(*this) || consequent;
}

proposition
proposition::iff( const proposition& equivalent ) const{
  return this->implies( equivalent ) && equivalent.implies( *this );
}

bool
proposition::evaluate( const set<string>& facts ) const{
  return mValue->evaluate( facts );
}

set<set<string> >
proposition::solve( const set<string>& variables ) const{
  set<set<string> > assignments;
  size_t max = pow( 2, variables.size() );

  // mask used to describe which elements from variables should be tested
  // and is then incremented to retrieve the next 'permutation'
  for( size_t mask = 0; mask < max; ++mask ){
    set<string> test;

    // each element of variables is mapped to a bit in mask
    // each bit is tested, and each element of variables is added appropriately
    size_t j = 1;
    for( auto var : variables ){
      if( j & mask ){
        test.insert( var );
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

set<set<string> >
proposition::solve2( set<string> variables ) const{
  return mValue->solve( variables );
}

proposition
gsw::operator""_lvar( const char* name, size_t sz ){
  auto var = make_shared<proposition::variable>();

  var->name = string( name, sz );

  return {var};
}

