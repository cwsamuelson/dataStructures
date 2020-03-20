#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<segment_tree.hh>

using namespace gsw;
using namespace std;

TEST_CASE("Segment trees (such as quad tree and octree)", "[segment_tree]") {
  SECTION("A segment tree can be specified in any dimension") {
    SECTION("1-Dimensional") {
      using tree = double_tree<int>;
      using item = tree::item;
      tree t{{{ 0 }},
             {{ 100 }}};

      t.insert({ 42, {{ 25 }}});
      t.insert({ 50, {{ 75 }}});

      CHECK(t.get_groups() == set<set<item>>{{{ 42, {{ 25 }}}},
                                             {{ 50, {{ 75 }}}}});

      t.insert({ 40, {{ 20 }}});
      t.insert({ 45, {{ 70 }}});

      CHECK(t.get_groups() == set<set<item>>{{{ 42, {{ 25 }}}, { 40, {{ 20 }}}},
                                             {{ 50, {{ 75 }}}, { 45, {{ 70 }}}}});

      t.insert({ 44, {{ 18 }}});

      CHECK(t.get_groups() == set<set<item>>{{{ 44, {{ 18 }}}, { 40, {{ 20 }}}},
                                             {{ 42, {{ 25 }}}},
                                             {{ 50, {{ 75 }}}, { 45, {{ 70 }}}}});
    }

    SECTION("2-Dimensional") {

    }

    SECTION("3-Dimensional") {

    }
  }
  double_tree<int> dt{{{ 0 }},
                      {{ 100.0 }}};
  quad_tree<double> qt{{{ 0.0,   0.0 }},
                       {{ 100.0, 100.0 }}};
  using dt_item = double_tree<int>::item;
  using qt_item = quad_tree<double>::item;

  qt.insert({ 12.0, {{ 25, 25 }}});
  qt.insert({ 15.0, {{ 20, 20 }}});

  CHECK(qt.get_groups() == set<set<qt_item>>{{{ 12.0, {{ 25, 25 }}}, { 15.0, {{ 20, 20 }}}}});

  qt.insert({ 18.0, {{ 75, 75 }}});
  qt.insert({ 21.0, {{ 70, 70 }}});

  CHECK(qt.get_groups() == set<set<qt_item>>{{{ 12.0, {{ 25, 25 }}}, { 15.0, {{ 20, 20 }}}},
                                             {{ 12.0, {{ 25, 25 }}}, { 15.0, {{ 20, 20 }}}}});

  qt.insert({ 24.0, {{ 71, 71 }}});

  CHECK(qt.get_groups() == set<set<qt_item>>{{{ 12.0, {{ 25, 25 }}}, { 15.0, {{ 20, 20 }}}},
                                             {{ 24.0, {{ 71, 71 }}}, { 21.0, {{ 70, 70 }}}},
                                             {{ 18.0, {{ 75, 75 }}}}});

  SECTION("too many objects in a region after a split splits again") {
  }
}
