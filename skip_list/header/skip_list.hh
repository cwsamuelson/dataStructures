#ifndef __SKIP_LIST_HH__
#define __SKIP_LIST_HH__

#include<utility>
#include<random>

#include<normal_iterator.hh>

namespace gsw {

#if 0
template<typename KEY, typename VALUE>
class skip_list{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using size_type = size_t;
  using storage_type = std::pair<key_type, value_type>;
  using iterator = normal_iterator<storage_type, skip_list>;

private:
  class node{
  public:
    storage_type data;
    size_type upper_index;
    bool points_up = false;

    node() = default;

    node( const storage_type& d )
      : data( d ){
    }
  };

  std::random_device rd;
  std::mt19937 rate;
  std::uniform_int_distribution<> gene;

  std::vector<std::vector<node> > mData;

  node&
  find( const key_type& key ){
    if( mData.empty() ){
      throw;
    }

    node& result = head;
    for( auto& row : mData ){
      for( auto& obj : row ){
        if( obj.data.first == key ){
          return obj.data;
        }
      }
    }

    throw;
  }

public:
  skip_list()
    : rd()
    , rate( rd() )
    , gene( 0, 1 )
    , mData(){
  }

  ~skip_list(){
    mData.clear();
  }

  void
  clear(){
  }

  bool
  empty() const{
    return true;
  }

  value_type&
  operator[]( const key_type& key ){
    return find( key ).second;
  }

  iterator
  insert( const storage_type& data ){
    if( head == nullptr ){
      head = new node( data );
      layer_count = 1;
    } else {
      node* location = find( data.first );
      node* next = new node( data );

      next->right = location->right;
      next->left = location;
      location->right = new node( data );

      if( next->right ){
        next->right->left = next;
      }

      unsigned int layer_index = 0;
      while( gene( rate )
          && layer_index < layer_count ){
        node* new_up = new node;

        new_up->down = next;
        next->up = new_up;
      }
    }
  }

  iterator
  begin(){
  }

  iterator
  end(){
  }
};
#endif
}

#endif
