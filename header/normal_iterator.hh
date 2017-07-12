#ifndef __NORMAL_ITERATOR_HH__
#define __NORMAL_ITERATOR_HH__

#include<iterator>

#include"additive.hh"

namespace gsw{

/*! Normalized iterator
 * @tparam TYPE  
 *
 * @tparam CONTAINER  
 *
 */
template<typename TYPE, typename CONTAINER, typename PTR_T = TYPE*>
class normal_iterator : public additive<normal_iterator<TYPE, CONTAINER>, long long>{
public:
  using container = CONTAINER;
  using value_type = TYPE;
  using pointer = PTR_T;
  using reference = value_type&;

protected:
  pointer mCurrent;

public:
  /*!
   * @param ptr  
   *
   */
  normal_iterator( pointer ptr ):
    mCurrent( ptr ){
  }

  /*!
   * @param iter  
   */
  normal_iterator( const normal_iterator& iter ):
    mCurrent( iter.mCurrent ){
  }

  /*!
   * @param other
   */
  unsigned int operator-( const normal_iterator& other ) const{
    return mCurrent - other.mCurrent;
  }

  /*!
   * @param mod  
   */
  normal_iterator& operator+=( long long mod ){
    mCurrent += mod;
    return *this;
  }

  /*!
   * @param mod  
   */
  normal_iterator& operator-=( long long mod ){
    mCurrent -= mod;
    return *this;
  }

  /*!
   * @param iter  
   */
  bool operator==( const normal_iterator& iter ) const{
    return mCurrent == iter.mCurrent;
  }

  /*!
   * @param iter  
   */
  bool operator!=( const normal_iterator& iter ) const{
    return !( ( *this ) == iter );
  }

  /*!
   * @param other  
   */
  bool operator<( const normal_iterator& other ) const{
    return mCurrent < other.mCurrent;
  }

  /*!
   * @param other
   */
  bool operator>( const normal_iterator& other )const{
    return mCurrent > other.mCurrent;
  }

  /*!
   *
   */
  reference operator*() const{
    return *mCurrent;
  }

  /*!
   *
   */
  pointer operator->() const{
    return mCurrent;
  }

  /*!
   *
   */
  normal_iterator& operator++(){
    ++mCurrent;
    return *this;
  }

  /*!
   *
   */
  normal_iterator operator++( int ){
    return normal_iterator( mCurrent++ );
  }
  
  /*!
   *
   */
  normal_iterator& operator--(){
    --mCurrent;
    return *this;
  }

  /*!
   *
   */
  normal_iterator operator--( int ){
    return normal_iterator( mCurrent-- );
  }
};

}

namespace std{

template<class TYPE, class CONTAINER>
struct iterator_traits<gsw::normal_iterator<TYPE, CONTAINER> >{
public:
  typedef typename gsw::normal_iterator<TYPE, CONTAINER>::value_type value_type;
  typedef unsigned int difference_type;
  typedef random_access_iterator_tag iterator_category;
};

}

#endif

