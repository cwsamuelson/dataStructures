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
    REQUIRE( g.get_nodes() == set<int>{1, 2} );
    REQUIRE( g.get_edges() == set<graph<int>::edge>{{1, 2}, {2, 1}} );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.neighbors( 1 ) == set<int>{2} );
    REQUIRE( g.get_out_edges( 1 ) == set<graph<int>::edge>{{1, 2}} );
    REQUIRE( g.get_in_edges( 1 ) == set<graph<int>::edge>{{2, 1}} );

    REQUIRE( g.adjacent( 2, 1 ) );
    REQUIRE( g.neighbors( 2 ) == set<int>{1} );
    REQUIRE( g.get_out_edges( 2 ) == set<graph<int>::edge>{{2, 1}} );
    REQUIRE( g.get_in_edges( 2 ) == set<graph<int>::edge>{{1, 2}} );
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

  SECTION( "Several nodes" ){
    g.add_node( 3 );

    REQUIRE( !g.empty() );
    REQUIRE( g.node_count() == 3 );
    REQUIRE( g.edge_count() == 0 );
    REQUIRE( g.get_nodes() == set<int>{1, 2, 3} );

    g.add_edge( 1, 2 );
    g.add_edge( 1, 3, true );

    REQUIRE( g.edge_count() == 3 );
    REQUIRE( g.get_edges() == set<graph<int>::edge>{{1, 2}, {2, 1}, {1, 3}} );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.adjacent( 2, 1 ) );
    REQUIRE( g.adjacent( 1, 3 ) );
    REQUIRE( !g.adjacent( 3, 1 ) );

    REQUIRE( g.neighbors( 1 ) == set<int>{2, 3} );
    REQUIRE( g.neighbors( 2 ) == set<int>{1} );
    REQUIRE( g.neighbors( 3 ) == set<int>{} );

    REQUIRE( g.get_out_edges( 1 ) == set<graph<int>::edge>{{1, 2}, {1, 3}} );
    REQUIRE( g.get_out_edges( 2 ) == set<graph<int>::edge>{{2, 1}} );
    REQUIRE( g.get_out_edges( 3 ) == set<graph<int>::edge>{} );

    REQUIRE( g.get_in_edges( 1 ) == set<graph<int>::edge>{{2, 1}} );
    REQUIRE( g.get_in_edges( 2 ) == set<graph<int>::edge>{{1, 2}} );
    REQUIRE( g.get_in_edges( 3 ) == set<graph<int>::edge>{{1, 3}} );
  }

  SECTION( "Remove nodes" ){
    g.add_node( 3 );

    g.add_edge( 1, 2 );
    g.add_edge( 2, 3 );

    g.remove_node( 2 );

    REQUIRE( g.node_count() == 2 );
    REQUIRE( g.edge_count() == 0 );

    REQUIRE( g.get_nodes() == set<int>{1, 2} );
    REQUIRE( g.get_edges() == set<graph<int>::edge>{} );

    REQUIRE( g.get_out_edges( 1 ) == set<graph<int>::edge>{} );
    REQUIRE( g.get_out_edges( 3 ) == set<graph<int>::edge>{} );

    REQUIRE( g.get_in_edges( 1 ) == set<graph<int>::edge>{} );
    REQUIRE( g.get_in_edges( 3 ) == set<graph<int>::edge>{} );
  }

  SECTION( "Remove edges" ){
    g.add_node( 3 );

    g.add_edge( 1, 2 );
    g.add_edge( 1, 3 );

    g.remove_edge( 3, 1 );

    REQUIRE( g.edge_count() == 3 );
    REQUIRE( g.get_edges() == set<graph<int>::edge>{{1, 2}, {2, 1}, {1, 3}} );

    REQUIRE( g.adjacent( 1, 2 ) );
    REQUIRE( g.adjacent( 2, 1 ) );
    REQUIRE( g.adjacent( 1, 3 ) );
    REQUIRE( !g.adjacent( 3, 1 ) );

    REQUIRE( g.neighbors( 1 ) == set<int>{2, 3} );
    REQUIRE( g.neighbors( 2 ) == set<int>{1} );
    REQUIRE( g.neighbors( 3 ) == set<int>{} );

    REQUIRE( g.get_out_edges( 1 ) == set<graph<int>::edge>{{1, 2}, {1, 3}} );
    REQUIRE( g.get_out_edges( 2 ) == set<graph<int>::edge>{{2, 1}} );
    REQUIRE( g.get_out_edges( 3 ) == set<graph<int>::edge>{} );

    REQUIRE( g.get_in_edges( 1 ) == set<graph<int>::edge>{{2, 1}} );
    REQUIRE( g.get_in_edges( 2 ) == set<graph<int>::edge>{{1, 2}} );
    REQUIRE( g.get_in_edges( 3 ) == set<graph<int>::edge>{{1, 3}} );
  }

  SECTION( "Clear the graph" ){
    SECTION( "Clear empty graph" ){
      graph<int> h;
      REQUIRE( h.empty() );

      h.clear();

      REQUIRE( h.empty() );
      REQUIRE( h.node_count() == 0 );
      REQUIRE( h.edge_count() == 0 );
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
