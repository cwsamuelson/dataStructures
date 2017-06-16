#ifndef __NORMAL_ITERATOR_HH__
#define __NORMAL_ITERATOR_HH__

#include<iterator>

namespace gsw{

/*! Normalized iterator
 * @tparam TYPE  
 *
 * @tparam CONTAINER  
 *
 */
template<class TYPE, class CONTAINER>
class normal_iterator{
public:
  typedef CONTAINER container;
  typedef TYPE value_type;
  typedef value_type* pointer;
  typedef value_type& reference;

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
  normal_iterator operator+( int mod ) const{
    return normal_iterator( mCurrent + mod );
  }

  /*!
   * @param mod  
   */
  normal_iterator operator-( int mod ) const{
    return normal_iterator( mCurrent - mod );
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
  normal_iterator  operator++( int ){
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
  normal_iterator  operator--( int ){
    return normal_iterator( mCurrent-- );
  }
};

}

namespace std{

template<class TYPE, class CONTAINER>
struct iterator_traits<normal_iterator<TYPE, CONTAINER> >{
public:
  typedef typename normal_iterator<TYPE, CONTAINER>::value_type value_type;
  typedef unsigned int difference_type;
  typedef random_access_iterator_tag iterator_category;
};

}

#endif

