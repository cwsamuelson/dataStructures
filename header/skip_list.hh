#ifndef __SKIP_LIST_HH__
#define __SKIP_LIST_HH__

#include<utility>
#include<random>

#include<normal_iterator.hh>

namespace gsw{

template<typename KEY, typename VALUE>
class skip_list{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using storage_type = std::pair<key_type, value_type>;
  using iterator = normal_iterator<storage_type, skip_list>;

private:
  class node{
  public:
    node* up = nullptr;
    node* down = nullptr;
    node* left = nullptr;
    node* right = nullptr;

    storage_type data;

    node() = default;

    node( const storage_type& d )
      : data( d ){
    }
  };

  std::random_device rd;
  std::mt19937 rate;
  std::uniform_int_distribution<> gene;

  node* head;
  node* tail;
  unsigned int layer_count = 0;

  node*
  find( const key_type& key ){
    if( !head ){
      return nullptr;
    }

    node* result = head;
    while( result->right->data.first < key ){
      if( result->right ){
        result = result->right;
      } else {
        result = result->down->right;
      }
    }

    return result;
  }

public:
  skip_list()
    : rd()
    , rate( rd() )
    , gene( 0, 1 )
    , head( nullptr )
    , tail( nullptr ){
  }

  ~skip_list(){
    clear();
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
    return find( key )->data.second;
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

}

#endif

