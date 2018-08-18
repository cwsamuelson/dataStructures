#include<catch.hpp>

#include<lambda.hh>

using namespace gsw;

TEST_CASE( "literals", "[lambda]" ){
  using X = Zero;

  REQUIRE( X :: value == 0 );
  REQUIRE( increment<X>  :: value == 1 );
  REQUIRE( succeed<X, 5> :: value == 5 );

  REQUIRE( eval<literal<succeed<X, 5> >, empty_env> :: result :: value == 5 );
}

TEST_CASE( "variables", "[lambda]" ){
  struct X{};
  struct Y{};
  using env1 = binding<Y, succeed<Zero, 12>,
               binding<X, succeed<Zero, 5> > >;
  using env2 = binding<Y, succeed<Zero, 15>,
               binding<X, succeed<Zero, 7> > >;

  using L1 = lookup<X, env1> :: result;
  using L2 = lookup<X, env2> :: result;
  using L3 = lookup<Y, env1> :: result;
  using L4 = lookup<Y, env2> :: result;

  REQUIRE( L1 :: value == 5 );
  REQUIRE( L2 :: value == 7 );
  REQUIRE( L3 :: value == 12 );
  REQUIRE( L4 :: value == 15 );

  using E1 = eval<ref<X>, env1> :: result;
  using E2 = eval<ref<X>, env2> :: result;
  using E3 = eval<ref<Y>, env1> :: result;
  using E4 = eval<ref<Y>, env2> :: result;

  REQUIRE( E1 :: value == 5 );
  REQUIRE( E2 :: value == 7 );
  REQUIRE( E3 :: value == 12 );
  REQUIRE( E4 :: value == 15 );
}

TEST_CASE( "conditionals", "[lambda]" ){
  struct X{};
  struct Y{};
  using env1 = binding<Y, succeed<Zero, 12>,
               binding<X, succeed<Zero, 5> > >;
  using env2 = binding<Y, succeed<Zero, 15>,
               binding<X, succeed<Zero, 7> > >;

  using E1 = eval<eval<If<literal<True>,
                          ref<X>,
                          ref<Y> >,
                       empty_env>
                  :: result, env1>
             :: result;
  using E2 = eval<eval<If<literal<False>,
                          ref<X>,
                          ref<Y> >,
                       empty_env>
                  :: result, env1>
             :: result;

  REQUIRE( E1 :: value == 5 );
  REQUIRE( E2 :: value == 12 );

  using E3 = eval<eval<If<literal<True>,
                          ref<X>,
                          ref<Y> >,
                       empty_env>
                  :: result, env2>
             :: result;
  using E4 = eval<eval<If<literal<False>,
                          ref<X>,
                          ref<Y> >,
                       empty_env>
                  :: result, env2>
             :: result;

  REQUIRE( E3 :: value == 7 );
  REQUIRE( E4 :: value == 15 );
}

TEST_CASE( "lambda", "[lambda]" ){
  struct X{};
  struct Y{};
  struct L{};
  using env1 = binding<Y, succeed<Zero, 12>,
               binding<X, succeed<Zero, 5> > >;
  using env2 = binding<Y, succeed<Zero, 15>,
               binding<X, succeed<Zero, 7> > >;

  using A = eval<apply<eval<lambda<L, literal<ref<X> > >, env1> :: result, Zero> :: result, env1> :: result;
  using B = eval<apply<eval<lambda<L, literal<ref<X> > >, env2> :: result, Zero> :: result, env1> :: result;
  REQUIRE( A :: value == 5 );//?
  REQUIRE( B :: value == 7 );//?
}
/*
TEST_CASE( "", "" ){
  struct X;
  struct main;
  struct argc;

  using main_args = binding<argc, Zero>;
  // main returns zero
  using main_l = lambda<main, Zero>;
  using main_c = eval<main_l, main_args>;
  using main_app = app<main_c, succeed<Zero, 5> >;

  using eval_result = eval<main_app, main_args>;
  REQUIRE( eval_result :: result == 0 );
}*/


/*
eval<app<lambda<X,
           ref<X> >,// how to increment X?
         ref<Y> >,
     env>
:: result :: value
==
eval<
  ref<Y>,// editable line
env> :: result :: value
*/
