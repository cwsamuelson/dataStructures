#ifndef __LIST_HH__
#define __LIST_HH__

/*!
 * @example test-list.cc
 */

#include<utility>

#include<normal_iterator.hh>

namespace gsw{

/*!
 * @tparam T
 *
 */
template<typename T>
class list{
public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using size_t = unsigned long;

private:
  /*!
   * @tparam U
   *
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
    node( Args... args ):
      data( std::forward<Args...>( args... ) ),
      next( nullptr ),
      prev( nullptr ){
    }
  };
  using node_type = node<value_type>;

  class node_iter{
  private:
/* maybe should be node_type? */
    node_type* mCurrent;

  public:
    node_iter( node_type* ptr ):
      mCurrent( ptr ){
    }

    node_iter( const node_iter& other ):
      mCurrent( other.mCurrent ){
    }

    node_iter& operator+=( long long mod ){
      while( mod-- && mCurrent->next ){
        mCurrent = mCurrent->next;
      }
      return *this;
    }

    node_iter& operator-=( long long mod ){
      while( mod-- && mCurrent->prev ){
        mCurrent = mCurrent->prev;
      }
      return *this;
    }

    bool operator==( const node_iter& other ) const{
      return mCurrent == other.mCurrent;
    }

    bool operator!=( const node_iter& other ) const{
      return !( *this == other );
    }

    reference operator*() const{
      return mCurrent->data;
    }

    pointer operator->() const{
      return &mCurrent->data;
    }

    node_iter& operator++(){
      if( mCurrent ){
        mCurrent = mCurrent->next;
      }
      return *this;
    }

    node_iter operator++( int ){
      node_iter ret( *this );

      if( mCurrent ){
        mCurrent = mCurrent->next;
      }
      return ret;
    }

    node_iter& operator--(){
      if( mCurrent ){
        mCurrent = mCurrent->prev;
      }
      return *this;
    }

    node_iter operator--( int ){
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
  /*!
   *
   */
  list():
    head( nullptr ),
    tail( nullptr ){
  }

  /*!
   * @param pos  
   *
   * @param value  
   *
   */
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

  /*!
   * @param pos  
   *
   * @return
   *
   */
  iterator erase( iterator pos ){
    iterator ret = pos.next;
    node_type* one = pos.mCurrent.prev;
    node_type* two = pos.mCurrent.next;

    one.next = two;
    two.prev = one;

    delete pos.mCurrent;

    return ret;
  }

  /*!
   * @return
   *
   */
  value_type pop_front(){
    value_type ret = front();
    node_type* rem = head;

    head = head->next;

    if( head == nullptr ){
      tail = nullptr;
    }

    delete rem;

    return ret;
  }

  /*!
   * @param value
   */
  value_type pop_back(){
    value_type ret = back();
    node_type* rem = tail;
 
    tail = tail->prev;

    if( tail == nullptr ){
      head = nullptr;
    }

    delete rem;

    return ret;
  }

  /*!
   * @param value  
   *
   */
  void push_front( const value_type& value ){
    if( head != nullptr ){
      node_type* first = head;

      head = new node_type( value );
      head->next = first;
      first->prev = head;
    } else {
      tail = head = new node_type( value );
    }
  }

  /*!
   * @param value
   *
   */
  void push_back( const value_type& value ){
    if( tail != nullptr ){
      node_type* last = tail;

      tail = new node_type( value );
      tail->prev = last;
      last->next = tail;
    } else {
      tail = head = new node_type( value );
    }
  }

  template<typename ...Args>
  void emplace_front( Args... args ){
    if( head != nullptr ){
      node_type* first = head;

      head = new node_type( std::forward<Args>( args )... );
      head->next = first;
      first->prev = head;
    } else {
      tail = head = new node_type( std::forward<Args>( args )... );
    }
  }

  template<typename ...Args>
  void emplace_back( Args... args ){
    if( tail != nullptr ){
      node_type* last = tail;

      tail = new node_type( std::forward<Args>( args )... );
      tail->prev = last;
      last->next = tail;
    } else {
      tail = head = new node_type( std::forward<Args>( args )... );
    }
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

    return cur->data;
  }

  iterator begin(){
    return iterator( node_iter( head ) );
  }
  iterator end(){
    return iterator( nullptr );
  }
  const iterator cbegin() const{
    return begin();
  }
  const iterator cend() const{
    return end();
  }

  list& merge( list&& other ){
  }

  bool empty(){
    return head == tail;
  }

  unsigned long size(){
    if( head != nullptr ){
      unsigned long count = 1;
      node_type* cur = head;

      while( cur->next != nullptr ){
        ++count;
        cur = cur->next;
      }

      return count;
    } else {
      return 0;
    }
  }
};

}

#endif

