#include<set>

#define CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS
#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<graph.hh>
#include<catch_stringify_helper.hh>

using namespace std;

TEST_CASE("", "[graph]") {
  gsw::graph<int> g;

  CHECK(g.empty());
  CHECK(g.node_count() == 0);
  CHECK(g.edge_count() == 0);

  g.add_node(1);

  CHECK(!g.empty());
  CHECK(g.node_count() == 1);
  CHECK(g.edge_count() == 0);

  g.add_node(2);

  CHECK(!g.empty());
  CHECK(g.node_count() == 2);
  CHECK(g.edge_count() == 0);

  SECTION("Undirected edge") {
    g.add_edge(1, 2);

    CHECK(!g.empty());
    CHECK(g.node_count() == 2);
    CHECK(g.edge_count() == 2);
    CHECK(g.get_nodes() == set<int>{ 1, 2 });
    CHECK(g.get_edges() == set<gsw::graph<int>::edge>{{ 1, 2 },
                                                      { 2, 1 }});

    CHECK(g.adjacent(1, 2));
    CHECK(g.neighbors(1) == set<int>{ 2 });
    CHECK(g.get_out_edges(1) == set<gsw::graph<int>::edge>{{ 1, 2 }});
    CHECK(g.get_in_edges(1) == set<gsw::graph<int>::edge>{{ 2, 1 }});

    CHECK(g.adjacent(2, 1));
    CHECK(g.neighbors(2) == set<int>{ 1 });
    CHECK(g.get_out_edges(2) == set<gsw::graph<int>::edge>{{ 2, 1 }});
    CHECK(g.get_in_edges(2) == set<gsw::graph<int>::edge>{{ 1, 2 }});
  }

  SECTION("Directed edge") {
    g.add_edge(1, 2, true);

    CHECK(!g.empty());
    CHECK(g.node_count() == 2);
    CHECK(g.edge_count() == 1);

    CHECK(g.adjacent(1, 2));
    CHECK(g.neighbors(1) == set<int>{ 2 });
    CHECK(g.get_out_edges(1) == set<gsw::graph<int>::edge>{{ 1, 2 }});
    CHECK(g.get_in_edges(1) == set<gsw::graph<int>::edge>{});

    CHECK(!g.adjacent(2, 1));
    CHECK(g.neighbors(2) == set<int>{});
    CHECK(g.get_out_edges(2) == set<gsw::graph<int>::edge>{});
    CHECK(g.get_in_edges(2) == set<gsw::graph<int>::edge>{{ 1, 2 }});

    CHECK(g.get_edges() == set<gsw::graph<int>::edge>{{ 1, 2 }});
  }

  SECTION("Circular ref") {
    g.add_edge(1, 1);

    CHECK(!g.empty());
    CHECK(g.node_count() == 2);
    CHECK(g.edge_count() == 1);

    CHECK(g.adjacent(1, 1));
    CHECK(g.neighbors(1) == set<int>{ 1 });
    CHECK(g.get_out_edges(1) == set<gsw::graph<int>::edge>{{ 1, 1 }});
    CHECK(g.get_in_edges(1) == set<gsw::graph<int>::edge>{{ 1, 1 }});

    CHECK(g.get_edges() == set<gsw::graph<int>::edge>{{ 1, 1 }});
  }

  SECTION("Several nodes") {
    g.add_node(3);

    CHECK(!g.empty());
    CHECK(g.node_count() == 3);
    CHECK(g.edge_count() == 0);
    CHECK(g.get_nodes() == set<int>{ 1, 2, 3 });

    g.add_edge(1, 2);
    g.add_edge(1, 3, true);

    CHECK(g.edge_count() == 3);
    CHECK(g.get_edges() == set<gsw::graph<int>::edge>{{ 1, 2 },
                                                      { 2, 1 },
                                                      { 1, 3 }});

    CHECK(g.adjacent(1, 2));
    CHECK(g.adjacent(2, 1));
    CHECK(g.adjacent(1, 3));
    CHECK(!g.adjacent(3, 1));

    CHECK(g.neighbors(1) == set<int>{ 2, 3 });
    CHECK(g.neighbors(2) == set<int>{ 1 });
    CHECK(g.neighbors(3) == set<int>{});

    CHECK(g.get_out_edges(1) == set<gsw::graph<int>::edge>{{ 1, 2 },
                                                           { 1, 3 }});
    CHECK(g.get_out_edges(2) == set<gsw::graph<int>::edge>{{ 2, 1 }});
    CHECK(g.get_out_edges(3) == set<gsw::graph<int>::edge>{});

    CHECK(g.get_in_edges(1) == set<gsw::graph<int>::edge>{{ 2, 1 }});
    CHECK(g.get_in_edges(2) == set<gsw::graph<int>::edge>{{ 1, 2 }});
    CHECK(g.get_in_edges(3) == set<gsw::graph<int>::edge>{{ 1, 3 }});
  }

  SECTION("Remove nodes") {
    g.add_node(3);

    g.add_edge(1, 2);
    g.add_edge(2, 3);

    g.remove_node(2);

    CHECK(g.node_count() == 2);
    CHECK(g.edge_count() == 0);

    CHECK(g.get_nodes() == set<int>{ 1, 3 });
    CHECK(g.get_edges() == set<gsw::graph<int>::edge>{});

    CHECK(g.get_out_edges(1) == set<gsw::graph<int>::edge>{});
    CHECK(g.get_out_edges(3) == set<gsw::graph<int>::edge>{});

    CHECK(g.get_in_edges(1) == set<gsw::graph<int>::edge>{});
    CHECK(g.get_in_edges(3) == set<gsw::graph<int>::edge>{});
  }

  SECTION("Remove edges") {
    g.add_node(3);

    g.add_edge(1, 2);
    g.add_edge(1, 3);

    g.remove_edge(3, 1);

    CHECK(g.edge_count() == 3);
    CHECK(g.get_edges() == set<gsw::graph<int>::edge>{{ 1, 2 },
                                                      { 2, 1 },
                                                      { 1, 3 }});

    CHECK(g.adjacent(1, 2));
    CHECK(g.adjacent(2, 1));
    CHECK(g.adjacent(1, 3));
    CHECK(!g.adjacent(3, 1));

    CHECK(g.neighbors(1) == set<int>{ 2, 3 });
    CHECK(g.neighbors(2) == set<int>{ 1 });
    CHECK(g.neighbors(3) == set<int>{});

    CHECK(g.get_out_edges(1) == set<gsw::graph<int>::edge>{{ 1, 2 },
                                                           { 1, 3 }});
    CHECK(g.get_out_edges(2) == set<gsw::graph<int>::edge>{{ 2, 1 }});
    CHECK(g.get_out_edges(3) == set<gsw::graph<int>::edge>{});

    CHECK(g.get_in_edges(1) == set<gsw::graph<int>::edge>{{ 2, 1 }});
    CHECK(g.get_in_edges(2) == set<gsw::graph<int>::edge>{{ 1, 2 }});
    CHECK(g.get_in_edges(3) == set<gsw::graph<int>::edge>{{ 1, 3 }});
  }

  SECTION("Clear the graph") {
    SECTION("Clear empty graph") {
      gsw::graph<int> h;
      CHECK(h.empty());

      h.clear();

      CHECK(h.empty());
      CHECK(h.node_count() == 0);
      CHECK(h.edge_count() == 0);
    }
    SECTION("Clear non-empty") {
      g.add_edge(1, 2);

      CHECK(!g.empty());

      g.clear();

      CHECK(g.empty());
      CHECK(g.node_count() == 0);
      CHECK(g.edge_count() == 0);
    }
  }
}
