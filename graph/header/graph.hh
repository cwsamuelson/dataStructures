#ifndef __GRAPH_HH__
#define __GRAPH_HH__

#include<utility>
#include<map>
#include<set>

namespace gsw {

//TODO: consider associating data with edges
//associating data with a node is meaningless for this data structure; this
//  information is more appropriately stored at the client.  However the data of
//  existing edges is intrinsically stored and tracked in this class, and could
//  be useful to obtain.  Data could be things like edge weight (or cost)
/*!Type to store/track/interact with graphs.
 *
 * @tparam T data type to track nodes.  This can be an comparable type, but is
 *             preferred to be something that can compare quickly and has small
 *             storage, particularly for larger graphs
 *
 * Stores graphs, and allows for the retrieval of information about the graph,
 * and its nodes/edges.  Can store graphs such as:
 * A-----B
 * |    / \
 * |   /   \
 * |  /    E
 * | /    /
 * |/    /
 * C----D
 * graph<char> g;
 *
 * g.add_node( 'A' );
 * g.emplace_edge( 'B', 'C' );
 * g.add_edge( 'A', 'C' );
 * g.add_edge( 'A', 'B' );
 * g.emplace_edge( 'E', 'E' );
 * g.add_edge( 'C', 'D' );
 * g.add_edge( 'B', 'E' );
 *
 * And information can be retrieved about the graph such as:
 * g.node_count() == 5;
 * g.edge_count() == 6;
 * g.get_nodes() == {'A', 'B', 'C', 'D', 'E'};
 * g.get_edges() == {{'A', 'B'}, {'B', 'A'}, {'A', 'C'}, {'C', 'A'}, etc...};
 * g.adjacent( 'A', 'B' ) == true;
 * g.adjacent( 'A', 'E' ) == false;
 * g.neighbors( 'B' ) == {'A', 'C', 'E'};
 *
 * The graph can also be traversed as:
 * set<node> visited_nodes;
 * set<node> nodes_to_visit = starting_node;
 *
 * while( !nodes_to_visit.empty() ){
 *   auto curr_node = get_next node( nodes_to_visit );
 *   auto neighbors = g.neighbors( curr_node );
 *   nodes_to_visit.insert( purge_visited_nodes( neighbors ) );
 *   visited_nodes.insert( neighbors );
 *
 *   // do something here!
 * }
 */
template<typename T>
class graph {
public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using edge = std::pair<value_type, value_type>;

private:
  //TODO:investigate multimap?
  std::map<value_type, std::set<value_type>> mNodes;

  //TODO:store a set of all known edges?
  // doing this may assist in removal of edges and nodes.
  // the mNodes map is effectively mOutEdges
  std::map<value_type, std::set<value_type>> mInEdges;

public:
  /*! Default ctor
   */
  graph() = default;

  /*! Add a node to the graph, with no connections
   *
   * @param ref value to refer to the new node by.
   */
  void add_node(const_reference ref) {
    mNodes[ref];
  }

  /*! Remove a node and all connections from the graph
   *
   * @param ref node to remove
   */
  void remove_node(const_reference ref) {
    auto outgoing = mNodes.at(ref);
    auto incoming = mInEdges.at(ref);

    for(auto out : outgoing) {
      auto& local = mInEdges.at(out);
      local.erase(local.find(ref));
    }

    for(auto in : incoming) {
      auto& local = mNodes.at(in);
      local.erase(local.find(ref));
    }

    mInEdges.erase(mInEdges.find(ref));
    mNodes.erase(mNodes.find(ref));
  }

  /*! Create a new edge between 2 nodes
   *
   * @param refA node to create edge from
   *
   * @param refB node to create edge to
   *
   * @param is_directed whether the edge should be directed or not
   */
  void add_edge(const_reference refA, const_reference refB, bool is_directed = false) {
    // test for existence of refB
    mNodes.at(refB);

    mNodes.at(refA).emplace(refB);
    mInEdges[refB].emplace(refA);

    if(!is_directed) {
      mNodes.at(refB).emplace(refA);
      mInEdges[refA].emplace(refB);
    }
  }

  /*! Remove edge between 2 nodes from graph
   *
   * @param refA node edge is from
   *
   * @param refB node edge is to
   */
  void remove_edge(const_reference refA, const_reference refB) {
    auto& outedges = mNodes.at(refA);
    outedges.erase(outedges.find(refB));

    auto& inedges = mInEdges.at(refB);
    inedges.erase(inedges.find(refA));
  }

  /*! Emplace new edge
   *
   * @param refA
   * @param refB
   * @param is_directed
   */
  void emplace_edge(const_reference refA, const_reference refB, bool is_directed = false) {
    mNodes[refA].emplace(refB);
    mInEdges[refB] = refA;

    if(!is_directed) {
      mNodes[refB].emplace(refA);
      mInEdges[refA] = refB;
    }
  }

  /*! Get all nodes in graph
   *
   * @return a set of all node names
   */
  [[nodiscard]]
  std::set<value_type> get_nodes() const {
    std::set<value_type> result;

    for(auto pr : mNodes) {
      result.emplace(pr.first);
    }

    return result;
  }

  /*! Get all edges in graph
   *
   * @return set of all edges, expressed as a pair of node names {node_from, node_to}
   */
  [[nodiscard]]
  std::set<edge> get_edges() const {
    std::set<edge> edges;

    for(auto node : mNodes) {
      for(auto edg : node.second) {
        edges.emplace(node.first, edg);
      }
    }

    return edges;
  }

  /*! Get all edges to and from a particular node
   *
   * @param ref node to get edges to/from
   *
   * @return set of edges to and from ref
   */
  [[nodiscard]]
  std::set<edge> get_edges(const_reference ref) const {
    auto result = get_out_edges(ref);

    auto in = get_in_edges(ref);

    result.insert(in.begin(), in.end());

    return result;
  }

  /*! Get all edges from a particular node
   *
   * @param ref node to get edges from
   *
   * @return set of edges from ref
   */
  [[nodiscard]]
  std::set<edge> get_out_edges(const_reference ref) const {
    std::set<edge> result;

    for(auto node : mNodes.at(ref)) {
      result.emplace(ref, node);
    }

    return result;
  }

  /*! Get all edges to a particular node
   *
   * @param ref node to get edges to
   *
   * @return set of edges to ref
   */
  [[nodiscard]]
  std::set<edge> get_in_edges(const_reference ref) const {
    std::set<edge> result;

    // verify node exists
    mNodes.at(ref);

    if(mInEdges.count(ref)) {
      for(auto node : mInEdges.at(ref)) {
        result.emplace(node, ref);
      }
    }

    return result;
  }

  /*! Test whether 2 nodes are connected
   *
   * @param refA First node to test connection
   *
   * @param refB Second node to test connection
   *
   * @return whether the refA and refB are adjacent
   */
  [[nodiscard]]
  bool adjacent(const_reference refA, const_reference refB) const {
    //return mNodes.at( refA ).contains( refB );//contains is c++20
    return mNodes.at(refA).count(refB) > 0;
    //!@todo should direction be accounted for here? guess is no
  }

  /*! Get a set of nodes adjacent to a particular node
   *
   * @param ref result is relative to
   *
   * @return set of neighbors to ref
   */
  [[nodiscard]]
  std::set<value_type> neighbors(const_reference ref) const {
    return mNodes.at(ref);
  }

  /*! Get the number of nodes in the graph
   *
   * @return the number of nodes in graph
   */
  [[nodiscard]]
  size_t node_count() const {
    return mNodes.size();
  }

  /*! Get the number of edges in the graph
   *
   * @return the number of edges in graph
   */
  [[nodiscard]]
  size_t edge_count() const {
    unsigned int count = 0;

    for(auto pr : mNodes) {
      count += pr.second.size();
    }

    return count;
  }

  /*! Empty the graph of all nodes and edges
   */
  void clear() {
    mNodes.clear();
    mInEdges.clear();
  }

  /*! Test whether the graph is empty
   */
  [[nodiscard]]
  bool empty() const {
    return mNodes.empty();
  }
};

}

#endif
