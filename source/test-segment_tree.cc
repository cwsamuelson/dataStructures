#include<catch.hpp>

#include<segment_tree.hh>

using namespace gsw;

TEST_CASE( "Segment trees (such as quad tree and octree)", "[segment_tree]" ){
  double_tree<int> dt{{{0}}, {{100.0}}};
  quad_tree<double> qt{{{0.0, 0.0}}, {{100.0, 100.0}}};
  using dt_item = double_tree<int>::item;
  using qt_item = quad_tree<double>::item;

  qt.insert( {12.0, {{25, 25}}} );
  qt.insert( {15.0, {{20, 20}}} );

  REQUIRE( qt.get_groups() == std::set<std::set<qt_item> >{{{12.0, {{25, 25}}},
                                                            {15.0, {{20, 20}}}}} );

  qt.insert( {18.0, {{75, 75}}} );
  qt.insert( {21.0, {{70, 70}}} );

  REQUIRE( qt.get_groups() == std::set<std::set<qt_item> >{{{12.0, {{25, 25}}},
                                                            {15.0, {{20, 20}}}},
                                                           {{12.0, {{25, 25}}},
                                                            {15.0, {{20, 20}}}}} );

  qt.insert( {24.0, {{71, 71}}} );

  REQUIRE( qt.get_groups() == std::set<std::set<qt_item> >{{{12.0, {{25, 25}}},
                                                            {15.0, {{20, 20}}}},
                                                           {{24.0, {{71, 71}}},
                                                            {21.0, {{70, 70}}}},
                                                           {{18.0, {{75, 75}}}}} );

  SECTION( "too many objects in a region after a split splits again" ){
  }
}
