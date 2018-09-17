#ifndef __GRAPH_HH__
#define __GRAPH_HH__

#include<map>
#include<set>

template<typename T>
class graph{
public:
  using value_type = T;
  using reference = T&;
  using iterator = /**/;

private:
  std::map<value_type, std::set<value_type> > mNodes;

public:
  void add_node( const reference ref );
  void add_edge( const reference refA, const reference refB, bool is_directed = false );
  void remove_edge( const reference refA, const reference refB );

  set get_nodes();
  set get_edges();

  set get_out_edges() const;
  set get_in_edges() const;

  size_t size() const;
  iterator begin();
  iterator end();
};

#endif
