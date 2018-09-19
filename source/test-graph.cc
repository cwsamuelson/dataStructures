#include<catch.hpp>

TEST_CASE( "", "[graph]" ){
  graph<int> g;

  REQUIRE( g.empty() );
  REQUIRE( g.node_count() == 0 );
  REQUIRE( g.edge_count() == 0 );

  g.add_node( 1 );

  REQUIRE( !g.empty() );
  REQUIRE( g.node_count() == 1 );
  REQUIRE( g.edge_count() == 0 );

  g.add_node( 2 );

  REQUIRE( !g.empty() );
  REQUIRE( g.node_count() == 2 );
  REQUIRE( g.edge_count() == 0 );

  SECTION( "Undirected edge" ){
    g.add_edge( 1, 2 );

    REQUIRE( !g.empty() );
    REQUIRE( g.node_count() == 2 );
    REQUIRE( g.edge_count() == 1 );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.neighbors( 1 ) == {2} );
    REQUIRE( g.get_out_edges( 1 ) == {1, 2} );
    REQUIRE( g.get_in_edges( 1 ) == {2, 1} );

    REQUIRE( g.adjacent( 2, 1 ) );
    REQUIRE( g.neighbors( 2 ) == {1} );
    REQUIRE( g.get_out_edges( 2 ) == {2, 1} );
    REQUIRE( g.get_in_edges( 2 ) == {1, 2} );

    REQUIRE( g.get_edges() == {{1, 2}, {2, 1}} );
  }

  SECTION( "Directed edge" ){
    g.add_edge( 1, 2, true );

    REQUIRE( !g.empty() );
    REQUIRE( g.node_count() == 2 );
    REQUIRE( g.edge_count() == 1 );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.neighbors( 1 ) == {2} );
    REQUIRE( g.get_out_edges( 1 ) == {{1, 2}} );
    REQUIRE( g.get_in_edges( 1 ) == {} );

    REQUIRE( g.adjacent( 2, 1 ) );
    REQUIRE( g.neighbors( 2 ) == {1} );
    REQUIRE( g.get_out_edges( 2 ) == {} );
    REQUIRE( g.get_in_edges( 2 ) == {1, 2} );

    REQUIRE( g.get_edges() == {{1, 2}} );
  }

  SECTION( "" ){
    g.clear();

    REQUIRE( g.empty() );
    REQUIRE( g.node_count() == 0 );
    REQUIRE( g.edge_count() == 0 );
  }
}
