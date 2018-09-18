#ifndef __GRAPH_HH__
#define __GRAPH_HH__

#include<utility>
#include<map>
#include<set>

//TODO: consider associating data with edges
//associating data with a node is meaningless for this data structure; this
//  information is more appropriately stored at the client.  However the data of
//  existing edges is intrinsically stored and tracked in this class, and could
//  be useful to obtain.
/*!
 * @tparam T
 */
template<typename T>
class graph{
public:
  using value_type = T;
  using reference = T&;
  using iterator = /**/;
  using edge = std::pair<value_type, value_type>;

private:
  std::map<value_type, std::set<value_type> > mNodes;

public:
  void
  add_node( const reference ref );
  void
  remove_node( const reference ref );

  void
  add_edge( const reference refA, const reference refB, bool is_directed = false );
  void
  remove_edge( const reference refA, const reference refB );

  set<value_type>
  get_nodes() const;
  set<edge>
  get_edges() const;//?

  set<edge>
  get_out_edges() const;
  set<edge>
  get_in_edges() const;

  bool
  adjacent( const reference refA, const reference refB ) const;
  set<value_type>
  neighbors( const reference ref ) const;

  size_t
  node_count() const;
  size_t
  edge_count() const;

  void
  clear() const;
};

#endif
