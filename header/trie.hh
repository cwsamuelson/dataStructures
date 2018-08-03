#ifndef __TRIE_HH__
#define __TRIE_HH__

template<typename KEY, typename VALUE>
class trie{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using iterator = iter;

private:
  class node{
    // using a map slows down processing
    // managing some kind of array may speed things up (but also increase memory footprint)
    // maybe should provide facilities to do either?
    // unordered_map might give both
    // the irony here is using a map to implement what is to be a map
    std::map<key_type::value_type, node> mChildren;
    bool mEndOfWord;
  };

  node mRoot;

public:
  trie() = default;

  void
  insert( const key_type& kt ){
    node* curr = &mRoot;

    for( auto ch : kt ){
      curr = &curr->mChildren[ch];
    }

    curr->mEndOfWord = true;
  }

  bool
  contains( const key_type& kt ) const{
    node* curr = &mRoot;

    for( auto ch : kt ){
      //c++20 provides a contains facility
      //if( curr->mChildren.contains( ch ) ){
      if( curr->mChildren.count( ch ) > 0 ){
        curr = &curr->mChildren.at( ch );
      } else {
        return false;
      }
    }

    return curr->mEndOfWord;
  }

  void
  erase( const key_type& kt ){
    // this erase does not delete the node from the tree
    node* curr = &mRoot;

    for( auto ch : kt ){
      curr = &curr->mChildren.at( cha );
    }

    curr->mEndOfWord = false;
  }

/*  find
  count
  value_type get
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

