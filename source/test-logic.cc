#include<catch.hpp>

#include<logic.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "Logic operators behave as expected", "[logic]" ){
  SECTION( "Basic operation" ){
    REQUIRE( ( "foo"_lvar ).evaluate( {"foo"} ) ); // trivially true
    REQUIRE(!( "foo"_lvar ).evaluate( {} ) );      // trivially false
    REQUIRE( ( "foo"_lvar ).solve( {"foo"} ) ==
             set<set<string> > {{"foo"}} );

    REQUIRE( ( "foo"_lvar ).solve( {"bar"} ) ==
             set<set<string> > {} );
  }

  SECTION( "Negation" ){
    SECTION( "Basic negation" ){
      REQUIRE( ( !"foo"_lvar ).evaluate( {} ) );
      REQUIRE(!( !"foo"_lvar ).evaluate( {"foo"} ) );
      // The only existing solution is foo being false
      // which is represented by empty set
      REQUIRE( ( !"foo"_lvar ).solve( {"foo"} ) == 
               set<set<string> > {{}} );
    }

    SECTION( "Double negation" ){
      REQUIRE( ( !!"foo"_lvar ).evaluate( {"foo"} ) );
      REQUIRE( ( !!"foo"_lvar ).solve( {"foo"} ) ==
               set<set<string> > {{"foo"}} );
    }
  }

  SECTION( "Conjunction (and)" ){
    REQUIRE( ( "foo"_lvar && "bar"_lvar ).evaluate( {"foo", "bar"} ) );
    REQUIRE(!( "foo"_lvar && "bar"_lvar ).evaluate( {"bar"} ) );
    REQUIRE(!( "foo"_lvar && "bar"_lvar ).evaluate( {"foo"} ) );
    REQUIRE(!( "foo"_lvar && "bar"_lvar ).evaluate( {} ) );
    REQUIRE( ( !"foo"_lvar && !"bar"_lvar ).evaluate( {} ) );
    REQUIRE( ( "foo"_lvar && "bar"_lvar ).solve( {"foo", "bar"} ) ==
             set<set<string> >( {{"foo", "bar"}} ) );
  }

  SECTION( "Disjunction (or)" ){
    REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate( {"foo", "bar"} ) );
    REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate( {"bar"} ) );
    REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate( {"foo"} ) );
    REQUIRE(!( "foo"_lvar || "bar"_lvar ).evaluate( {} ) );
    REQUIRE( ( "foo"_lvar || "bar"_lvar ).solve( {"foo", "bar"} ) ==
             set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Exclusive disjunction (xor)" ){
    REQUIRE(!( "foo"_lvar ^ "bar"_lvar ).evaluate( {"foo", "bar"} ) );
    REQUIRE( ( "foo"_lvar ^ "bar"_lvar ).evaluate( {"bar"} ) );
    REQUIRE( ( "foo"_lvar ^ "bar"_lvar ).evaluate( {"foo"} ) );
    REQUIRE(!( "foo"_lvar ^ "bar"_lvar ).evaluate( {} ) );
    REQUIRE( ( "foo"_lvar ^ "bar"_lvar ).solve( {"foo", "bar"} ) ==
             set<set<string> >( {{"foo"}, {"bar"}} ) );
  }

  SECTION( "Implication" ){
    REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {"foo", "bar"} ) );
    REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {"bar"} ) );
    REQUIRE(!( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {"foo"} ) );
    REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {} ) );
    // foo and bar both false is a valid answer, so empty set is included
    REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).solve( {"foo", "bar"} ) ==
             set<set<string> >( {{"foo", "bar"}, {"bar"}, {}} ) );
  }

  SECTION( "Tautology (equivalence, iff)" ){
    REQUIRE( ( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {"foo", "bar"} ) );
    REQUIRE(!( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {"bar"} ) );
    REQUIRE(!( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {"foo"} ) );
    REQUIRE( ( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {} ) );
    // foo and bar both false is a valid answer, so empty set is included
    REQUIRE( ( "foo"_lvar.iff( "bar"_lvar ) ).solve( {"foo", "bar"} ) ==
             set<set<string> >( {{"foo", "bar"}, {}} ) );
  }

  SECTION( "Can form logic sentences" ){
    auto prop = ( "A"_lvar && !"B"_lvar ).implies( "C"_lvar ) && ( !"A"_lvar ).iff( "B"_lvar && "C"_lvar );
    int i = 0;
    for( auto solution : prop.solve( {"A", "B", "C"} ) ){
      REQUIRE( prop.evaluate( solution ) );
      ++i;
    }
    REQUIRE( i == 3 );
  }
}

