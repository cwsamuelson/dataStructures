#ifndef __LIST_HH__
#define __LIST_HH__

#include<normal_iterator.hh>

class list_iterator;

template<typename T>
class list{
public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using size_t = unsigned long;
  using iterator = list_iterator;

private:
  template<typename U>
  class node{
  public:
    using value_type = U;
    using reference = U&;
    using pointer = U*;

    value_type data;
    node* next;
    node* prev;

    template<typename Args...>
    node( Args... args ):
      data( std::forward<Args...>( args... ) ){
    }
    node( const reference value ):
      data( value ){
    }
    node( value_type&& value ):
      data( forward( value ) ){
    }
  };
  using node_type = node<value_type>;
  friend class list_iterator;

  node_type* head;
  node_type* tail;

public:
  list():
    head( nullptr ),
    tail( nullptr ){
  }

  iterator insert( iterator pos, const value_type& value ){
    node_type* next = new node_type( value );
    node_type* current = pos.mCurrent;
    node_type* last = current.next;

    next.prev = current;
    next.next = last;

    current.next = next;
    last.prev = next;

    return iterator( next );
  }
  iterator erase( iterator pos ){
    iterator ret = pos.next;
    node_type* one = pos.mCurrent.prev;
    node_type* two = pos.mCurrent.next;

    one.next = two;
    two.prev = one;

    delete pos.mCurrent;

    return ret;
  }

  void push_front( const value_type& value ){
    node* first = head;

    head = new node( value );
    head->next = first;
  }
  template<typename U>
  void push_front( U&& value ){
    //correct usage of perfect forwarding?
    //std::forward<U>
  }
  value_type pop_front(){
    value_type ret = front();
    node* rem = head;

    head = head->next;

    if( head == nullptr ){
      tail = nullptr;
    }

    delete rem;

    return ret;
  }
  template<typename ...Args>
  void emplace_front
  void push_back( const value_type& value ){
    emplace_back( value );
  }
  void push_back( value_type&& value )
  value_type pop_back(){
    value_type ret = back();
    node* rem = tail;
 
    tail = tail->prev;

    if( tail == nullptr ){
      head = nullptr;
    }

    delete rem;

    return ret;
  }
  template<typename ...Args>
  void emplace_back( Args... args ){
    node* last = tail;

    tail = new node( args... );
    tail->prev = last;
  }

  reference front(){
    return head->data;
  }
  reference back(){
    return tail->data;
  }
  reference operator[]( size_t idx ){
    node_type* cur = head;

    while( idx != 0 ){
      cur = cur->next;
      --idx;
    }

    return node->data;
  }

  iterator begin(){
    return list_iterator( head );
  }
  iterator end(){
    return list_iterator( nullptr );
  }
  const iterator begin() const{
    return begin();
  }
  const iterator end() const{
    return end();
  }

  list& merge( list&& other ){
  }

  bool empty(){
    return head == tail;
  }
  unsigned long size(){
    unsigned long count = 0;
    node_type* cur = head;

    while( cur->next != tail ){
      ++count;
      cur = cur->next;
    }

    return count + 1;
  }
};

template<typename T>
class list_iterator{
public:
  using value_type = TYPE;
  using pointer = value_type*;
  using reference = value_type&;

protected:
  using node_type = list<T>::node_type;
  node_type* mCurrent;

public:
  list_iterator( node_type* node ):
    mCurrent( node ){
  }
  list_iterator( const list_iterator& other ):
    mCurrent( other.mCurrent ){
  }
  list_iterator( list_iterator&& other ):
    mCurrent( other.mCurrent ){
    other.mCurrent = nullptr;
  }

  bool operator==( const list_iterator& other ) const{
    return mCurrent == other.mCurrent;
  }
  bool operator!=( const list_iterator& other ) const{
    return !( ( *this ) == other );
  }

  reference operator*() const{
    return *mCurrent;
  }
  pointer operator->() const{
    return mCurrent;
  }

  list_iterator& operator++(){
    mCurrent = mCurrent.next;
    return *this;
  }
  list_iterator operator++( int ){
    return list_iterator( mCurrent.next );
  }
  list_iterator& operator--(){
    mCurrent = mCurrent.prev;
    return *this;
  }
  list_iterator operator--( int ){
    return list_iterator( mCurrent.prev );
  }

};

#endif

