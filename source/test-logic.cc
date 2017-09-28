#include<catch.hpp>

#include<logic.hh>

using namespace std;
using namespace gsw;

TEST_CASE( "", "[logic]" ){
  REQUIRE( ( "foo"_lvar ).evaluate( {"foo"} ) ); // trivially true
  REQUIRE( ( "foo"_lvar ).evaluate_all( {"foo"} )
           == set<set<string>> {{"foo"}} );

  REQUIRE( ( !"foo"_lvar ).evaluate( {} ) ); // basic negation
  REQUIRE(!( !"foo"_lvar ).evaluate( {"foo"} ) ); // basic negation
  REQUIRE( ( !"foo"_lvar ).evaluate_all( {"foo"} )
           == set<set<string>> {{}} );

  REQUIRE( ( !!"foo"_lvar ).evaluate( {"foo"} ) ); // double negation
  REQUIRE( ( !!"foo"_lvar ).evaluate_all( {"foo"} )
           == set<set<string>> {{"foo"}} );

  REQUIRE( ( "foo"_lvar && "bar"_lvar ).evaluate( {"foo", "bar"} ) ); // conjunction
  REQUIRE(!( "foo"_lvar && "bar"_lvar ).evaluate( {"bar"} ) ); // conjunction
  REQUIRE(!( "foo"_lvar && "bar"_lvar ).evaluate( {"foo"} ) ); // conjunction
  REQUIRE(!( "foo"_lvar && "bar"_lvar ).evaluate( {} ) ); // conjunction
  REQUIRE( ( "foo"_lvar && "bar"_lvar ).evaluate_all( {"foo", "bar"} )
           == set<set<string>>( {{"foo", "bar"}} ) );

  REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate( {"foo", "bar"} ) ); // disjunction
  REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate( {"bar"} ) ); // disjunction
  REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate( {"foo"} ) ); // disjunction
  REQUIRE(!( "foo"_lvar || "bar"_lvar ).evaluate( {} ) ); // disjunction
  REQUIRE( ( "foo"_lvar || "bar"_lvar ).evaluate_all( {"foo", "bar"} )
           == set<set<string>>( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );

  REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {"foo", "bar"} ) ); // implication
  REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {"bar"} ) ); // implication
  REQUIRE(!( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {"foo"} ) ); // implication
  REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate( {} ) ); // implication
  REQUIRE( ( "foo"_lvar.implies( "bar"_lvar ) ).evaluate_all( {"foo", "bar"} )
           == set<set<string>>( {{"foo", "bar"}, {"bar"}, {}} ) );

  REQUIRE( ( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {"foo", "bar"} ) ); // equivalence
  REQUIRE(!( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {"bar"} ) ); // equivalence
  REQUIRE(!( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {"foo"} ) ); //equivalence
  REQUIRE( ( "foo"_lvar.iff( "bar"_lvar ) ).evaluate( {} ) ); // equivalence
  REQUIRE( ( "foo"_lvar.iff( "bar"_lvar ) ).evaluate_all( {"foo", "bar"} )
           == set<set<string>>( {{"foo", "bar"}, {}} ) );

  auto prop = ("A"_lvar && !"B"_lvar).implies("C"_lvar) && (!"A"_lvar).iff("B"_lvar && "C"_lvar);
  int i = 0;
  for( auto solution : prop.evaluate_all( {"A", "B", "C"} ) ){
    REQUIRE( prop.evaluate( solution ) );
    ++i;
  }
  REQUIRE( i == 3 );
}

