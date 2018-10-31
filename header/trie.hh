#ifndef __TRIE_HH__
#define __TRIE_HH__

#include<set>
#include<memory>
#include<queue>

/*!
 * @tparam key
 * @tparam VALUE
 */
template<typename KEY, typename VALUE>
class prefix_tree{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using iterator = iter;

private:
  struct node{
    // using a map slows down processing
    // managing some kind of array may speed things up (but also increase memory footprint)
    // maybe should provide facilities to do either?
    // unordered_map might give both
    // the irony here is using a map to implement what is to be a type of map
    std::map<key_type::value_type, node> mChildren;
    std::unique_ptr<value_type> mData;
  };

  node*
  seek_node( const key_type& key ){
    node* curr = &mRoot;

    for( auto ch : key ){
      //c++20 provides a contains facility
      //if( curr->mChildren.contains( ch ) ){
      if( curr->mChildren.count( ch ) > 0 ){
        curr = &curr->mChildren.at( ch );
      } else {
        return nullptr;
      }
    }

    return curr;
  }

  node mRoot;

public:
  prefix_tree() = default;

  void
  insert( const key_type& key, const value_type& value ){
    node* curr = &mRoot;

    for( auto ch : key ){
      curr = &curr->mChildren[ch];
    }

    curr->mData = make_unique( value );
  }

  bool
  contains( const key_type& kt ) const{
    auto nod = seek_node( kt );

    return nod ? nod->mData : false;
  }

  void
  erase( const key_type& key ){
    node* nod = seek_node( key );

    if( nod && nod->mData ){
      std::unique_ptr<value_type> ptr;
      ptr.swap( nod->mData );
    }

    curr->mEndOfWord = false;
  }

  std::set<value_type>
  find( const key_type& key ) const{
    std::set<value_type> results;
    std::queue<node*> node_que;

    node_que.push( seek_node( key ) );

    while( !node_que.empty() ){
      node* ptr = node_que.front();
      node_que.pop();

      if( ptr->mData ){
        results.insert( ptr->mData );
      }

      std::transform( nod->mChildren.begin(), nod->mChildren.end(),
                      std::inserter( node_que, node_que.begin() ),
                      []( auto pair ){
                        return pair.second;
                      } );
    }

    return results;
  }

  size_type
  count( const key_type& key = key_type() ) const{
    std::queue<node*> node_que;
    size_type count = 0;

    node_que.push( seek_node( key ) );

    while( !node_que.empty() ){
      node* ptr = node_que.front();
      node_que.pop();

      if( ptr->mData ){
        ++count;
      }

      std::transform( nod->mChildren.begin(), nod->mChildren.end(),
                      std::inserter( node_que, node_que.begin() ),
                      []( auto pair ){
                        return pair.second;
                      } );
    }
  }

/*value_type get
  value_type getBest
  iterator begin
  iterator end*/

  bool
  empty() const{
    return mRoot.mChildren.empty();
  }

  void
  clear(){
    mRoot.mChildren.clear();
  }
};

#endif
