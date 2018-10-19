#ifndef __LIST_HH__
#define __LIST_HH__

/*!
 * @example test-list.cc
 */

#include<utility>

#include<normal_iterator.hh>

namespace gsw{

/*! Linked list
 *
 * @tparam T Type of data stored in list
 */
template<typename T>
class list{
public:
  using value_type = T;
  using reference  = T&;
  using pointer    = T*;
  using size_t     = unsigned long;

private:
  /*! Node containing data within list
   *
   * @tparam U Type of data stored in node
   */
  template<typename U>
  class node{
  public:
    using value_type = U;
    using reference = U&;
    using pointer = U*;

    value_type data;
    node* next;
    node* prev;

    template<typename ...Args>
    node( Args... args )
      : data( std::forward<Args>( args )... )
      , next( nullptr )
      , prev( nullptr ){
    }
  };
  using node_type = node<value_type>;

  class node_iter{
  private:
/* maybe should be node_type? */
    node_type* mCurrent;

  public:
    node_iter( node_type* ptr )
      : mCurrent( ptr ){
    }

    node_iter( const node_iter& other )
      : mCurrent( other.mCurrent ){
    }

    node_iter&
    operator+=( long long mod ){
      while( mod-- && mCurrent->next ){
        mCurrent = mCurrent->next;
      }
      return *this;
    }

    node_iter&
    operator-=( long long mod ){
      while( mod-- && mCurrent->prev ){
        mCurrent = mCurrent->prev;
      }
      return *this;
    }

    bool
    operator==( const node_iter& other ) const{
      return mCurrent == other.mCurrent;
    }

    bool
    operator!=( const node_iter& other ) const{
      return !( *this == other );
    }

    reference
    operator*() const{
      return mCurrent->data;
    }

    pointer
    operator->() const{
      return &mCurrent->data;
    }

    node_iter&
    operator++(){
      if( mCurrent ){
        mCurrent = mCurrent->next;
      }
      return *this;
    }

    node_iter
    operator++( int ){
      node_iter ret( *this );

      if( mCurrent ){
        mCurrent = mCurrent->next;
      }
      return ret;
    }

    node_iter&
    operator--(){
      if( mCurrent ){
        mCurrent = mCurrent->prev;
      }
      return *this;
    }

    node_iter
    operator--( int ){
      node_iter ret( *this );

      if( mCurrent ){
        mCurrent = mCurrent->prev;
      }
      return ret;
    }
  };

  node_type* head;
  node_type* tail;

public:
  using iterator = normal_iterator<value_type, list, node_iter>;

  /*! Default ctor
   */
  list()
    : head( nullptr )
    , tail( nullptr ){
  }

  /*! Insert new element at pos
   *
   * @param pos Iterator to location to place new element
   *
   * @param value New value to place in list
   *
   * @return iterator to new value
   */
  iterator
  insert( iterator pos, const value_type& value ){
    node_type* next = new node_type( value );
    node_type* current = pos.mCurrent;
    node_type* last = current.next;

    next.prev = current;
    next.next = last;

    current.next = next;
    last.prev = next;

    return iterator( next );
  }

  /*! Erase element at pos
   *
   * @param pos Iterator to element to remove
   *
   * @return Iterator to element now at same position
   */
  iterator
  erase( iterator pos ){
    iterator ret = pos.next;
    node_type* one = pos.mCurrent.prev;
    node_type* two = pos.mCurrent.next;

    one.next = two;
    two.prev = one;

    delete pos.mCurrent;

    return ret;
  }

  /*! Remove front element
   *
   * @return Copy of element that was at the front
   */
  value_type
  pop_front(){
    value_type ret = front();
    node_type* rem = head;

    head = head->next;

    if( head == nullptr ){
      tail = nullptr;
    }

    delete rem;

    return ret;
  }

  /*! Remove back element
   *
   * @return Copy of element that was at the back
   */
  value_type
  pop_back(){
    value_type ret = back();
    node_type* rem = tail;

    tail = tail->prev;

    if( tail == nullptr ){
      head = nullptr;
    }

    delete rem;

    return ret;
  }

  /*! Create copy of value at front of list
   *
   * @param value
   */
  void
  push_front( const value_type& value ){
    if( head != nullptr ){
      node_type* first = head;

      head = new node_type( value );
      head->next = first;
      first->prev = head;
    } else {
      tail = head = new node_type( value );
    }
  }

  /*! Create copy of value at back of list
   *
   * @param value
   */
  void
  push_back( const value_type& value ){
    if( tail != nullptr ){
      node_type* last = tail;

      tail = new node_type( value );
      tail->prev = last;
      last->next = tail;
    } else {
      tail = head = new node_type( value );
    }
  }

  /*! Construct a new object at front of the list
   *
   * @tparam ...Args Types of arguments to be forwarded to new object
   *
   * @param args Arguments to be passed to constructor of new object
   */
  template<typename ...Args>
  void
  emplace_front( Args... args ){
    if( head != nullptr ){
      node_type* first = head;

      head = new node_type( std::forward<Args>( args )... );
      head->next = first;
      first->prev = head;
    } else {
      tail = head = new node_type( std::forward<Args>( args )... );
    }
  }

  /*! Construct a new object at back of the list
   *
   * @tparam ...Args Types of arguments to be forwarded to new object
   *
   * @param args Arguments to be passed to constructor of new object
   */
  template<typename ...Args>
  void
  emplace_back( Args... args ){
    if( tail != nullptr ){
      node_type* last = tail;

      tail = new node_type( std::forward<Args>( args )... );
      tail->prev = last;
      last->next = tail;
    } else {
      tail = head = new node_type( std::forward<Args>( args )... );
    }
  }

  /*! Examine front object of list
   *
   * @return Reference to the first object in the list
   */
  reference
  front(){
    return head->data;
  }

  /*! Examine back object of list
   *
   * @return Reference to the last object in the list
   */
  reference
  back(){
    return tail->data;
  }

  /*!
   */
  const reference
  front() const{
    return front();
  }

  /*!
   */
  const reference
  back() const{
    return back();
  }

  /*! Accessor operator
   *
   * @param idx Index of object in list of interest
   *
   * @return Object sitting at position idx
   */
  reference
  operator[]( size_t idx ){
    node_type* cur = head;

    while( idx-- != 0 ){
      cur = cur->next;
    }

    return cur->data;
  }

  /*! Obtain iterator to the beginning of the list
   *
   * @return Iterator to the beginning of the list
   */
  iterator
  begin(){
    return iterator( node_iter( head ) );
  }

  /*! Obtain iterator to the end of the list
   *
   * @return Iterator to the end of the list
   */
  iterator
  end(){
    return iterator( nullptr );
  }

  /*! Obtain const iterator to the beginning of the list
   *
   * @return const iterator to the beginning of the list
   */
  const iterator
  cbegin() const{
    return begin();
  }

  /*! Obtain const iterator to the end of the list
   *
   * @return const iterator to the end of the list
   */
  const iterator
  cend() const{
    return end();
  }

  /*!
   * @return
   */
  list&
  merge( list&& other ){
  }

  /*! Determine whether list is empty
   *
   * @return Empty-ness of list
   */
  bool
  empty(){
    return head == nullptr;
  }

  /*! Calculate list size
   *
   * @return Current size of the list
   */
  unsigned long
  size(){
    if( head == nullptr ){
      return 0;
    }

    unsigned long count = 1;
    node_type* cur = head;

    while( cur->next != nullptr ){
      ++count;
      cur = cur->next;
    }

    return count;
  }
};

}

#endif
