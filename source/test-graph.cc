#include<set>

#include<catch.hpp>

#include<graph.hh>

using namespace std;

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
    REQUIRE( g.edge_count() == 2 );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.neighbors( 1 ) == set<int>{2} );
    REQUIRE( g.get_out_edges( 1 ) == set<graph<int>::edge>{{1, 2}} );
    REQUIRE( g.get_in_edges( 1 ) == set<graph<int>::edge>{{2, 1}} );

    REQUIRE( g.adjacent( 2, 1 ) );
    REQUIRE( g.neighbors( 2 ) == set<int>{1} );
    REQUIRE( g.get_out_edges( 2 ) == set<graph<int>::edge>{{2, 1}} );
    REQUIRE( g.get_in_edges( 2 ) == set<graph<int>::edge>{{1, 2}} );

    REQUIRE( g.get_edges() == set<graph<int>::edge>{{1, 2}, {2, 1}} );
  }

  SECTION( "Directed edge" ){
    g.add_edge( 1, 2, true );

    REQUIRE( !g.empty() );
    REQUIRE( g.node_count() == 2 );
    REQUIRE( g.edge_count() == 1 );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.neighbors( 1 ) == set<int>{2} );
    REQUIRE( g.get_out_edges( 1 ) == set<graph<int>::edge>{{1, 2}} );
    REQUIRE( g.get_in_edges( 1 ) == set<graph<int>::edge>{} );

    REQUIRE( !g.adjacent( 2, 1 ) );
    REQUIRE( g.neighbors( 2 ) == set<int>{} );
    REQUIRE( g.get_out_edges( 2 ) == set<graph<int>::edge>{} );
    REQUIRE( g.get_in_edges( 2 ) == set<graph<int>::edge>{{1, 2}} );

    REQUIRE( g.get_edges() == set<graph<int>::edge>{{1, 2}} );
  }

  SECTION( "Clear the graph" ){
    SECTION( "Clear empty graph" ){
      REQUIRE( g.empty() );

      g.clear();

      REQUIRE( g.empty() );
      REQUIRE( g.node_count() == 0 );
      REQUIRE( g.edge_count() == 0 );
    }
    SECTION( "Clear non-empty" ){
      g.add_edge( 1, 2 );

      REQUIRE( !g.empty() );
      
      g.clear();

      REQUIRE( g.empty() );
      REQUIRE( g.node_count() == 0 );
      REQUIRE( g.edge_count() == 0 );
    }
  }
}
