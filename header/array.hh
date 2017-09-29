#ifndef __ARRAY_HH__
#define __ARRAY_HH__

/*!
 * @example test-array.cc
 */

#include<functional>
#include<vector>
#include<initializer_list>

#include<normal_iterator.hh>

namespace gsw{

//see mask_array and indirect array for indexing ideas
//  one allows data[data > 5] = -1 kinda syntax,
//  the other data[data2] = -2 syntax
//  each modifies a set of values
//  the first says values at indexes greater than 5 are set to -1
//  the other says values at indexes stored in data2 are set to -2

template<typename T>
class array;

/*!
 * @todo Performance testing on array splicing.  may be a faster way to do this
 */
template<typename T>
struct splice_index{
  typedef std::function<bool( T, T )> opsig;

  opsig mOp;
  unsigned int mIdx;

  splice_index( opsig op, unsigned int idx ):
    mOp( op ),
    mIdx( idx ){
  }
};

template<typename T>
struct splice_helper;

template<typename T, unsigned int N>
struct splice_helper<T[N]>{
  array<T[N]>& mArr;
  std::vector<unsigned int> mIdxs;

  splice_helper( array<T[N]>& arr ):
    mArr( arr ){
  }

  array<T[N]>& operator=( T t ){
    for( auto it : mIdxs ){
      mArr[it] = t;
    }

    return mArr;
  }
};

/*! Simple wrapper around builtin array
 *
 * @tparam T  Type of data stored in array
 *
 * @tparam N  Number of elements stored in array
 *
 * @todo This class is a good candidate to implement constexpr-ness
 */
template<typename T, unsigned int N>
class array<T[N]>{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef unsigned int index_t;
  static const index_t mSize = N;
  static const unsigned int ptrdiff = sizeof( value_type );
  typedef splice_index<value_type> splicer;
  typedef splice_helper<value_type[N]> helper;
  typedef normal_iterator<value_type, array> iterator;
  typedef const normal_iterator<value_type, array> const_iterator;

private:
  value_type mArr[mSize];

public:
  /*! Default ctor
   */
  constexpr array() = default;

  /*! List initialization ctor
   *
   * @tparam ...Args
   *
   * @param args
   */
  template<typename ...Args>
  constexpr array( Args... args ):
    mArr{ args...}{
  }

  /*! Get the size of the array
   *
   * @return The number of elements
   *
   * Returns the number of elements stored in the array.
   */
  constexpr index_t size() const{
    return mSize;
  }

  /*! Indexing operator retrieves element at given index
   *
   * @param idx  Index at which value will be retrieved
   */
  reference operator[]( index_t idx ){
    return mArr[idx];
  }

  /*! Index operator overload for const correctness
   *
   * @param idx  Index at which value will be retrieved
   *
   * Behaves the same as non-const version, but provides a const reference,
   * and can be used on const objects.
   */
  constexpr const_reference operator[]( index_t idx ) const{
    return mArr[idx];
  }

  /*! Index operator to allow for array splicing
   *
   * @param spl  Splicer object describing which elements to return
   *
   * @return Helper to allow assignment to elements described by splicer argument
   *
   * Utility operator to allow for more descriptive array modification.
   * Intended usage:
   * array<int[6]> arr;
   * arr[arr > 2] = 42;
   *
   * This will assign all elements at indexes 3 - 5 equal to 42.
   */
  helper operator[]( const splicer& spl ){
    helper h( *this );

    for( unsigned int i = 0; i < mSize; ++i ){
      if( spl.mOp( i, spl.mIdx ) ){
        h.mIdxs.push_back( i );
      }
    }

    return h;
  }

  /*! Index operator to allow for array splicing
   *
   * @tparam M  Size of array argument
   *
   * @param a  Array of elements list indexes to modify
   *
   * @return Helper to allow assignment to elements described by splicer argument
   *
   * @todo genericize to take other containers as well
   *
   * Utility operator to allow for more descriptive array modification.
   * Intended usage:
   * array<int[6]> arr1;
   * array<int[2]> arr2;
   *
   * arr2[0] = 3;
   * arr2[1] = 4;
   *
   * arr1[arr2] = 42;
   *
   * This will assign elements at indexes 3 and 4 equal to 42.
   */
  template<unsigned int M>
  helper operator[]( array<unsigned int[M]>& a ){
    helper h( *this );

    for( auto it : a ){
      h.mIdxs.push_back( it );
    }

    return h;
  }

  /*! GT operator for array splicing
   *
   * @param idx  Index, greater than which will be included in subsequent
   *             splicing operations
   */
  splicer operator>( index_t idx ){
    return splicer( std::greater<value_type>(), idx );
  }

  /*! GE operator for array splicing
   *
   * @param idx  Index, greater than and equal to which will be included in
   *             subsequent splicing operations
   */
  splicer operator>=( index_t idx ){
    return splicer( std::greater_equal<value_type>(), idx );
  }

  /*! LT operator for array splicing
   *
   * @param idx  Index, lesser than which will be included in subsequent
   *             splicing operations
   */
  splicer operator<( index_t idx ){
    return splicer( std::less<value_type>(), idx );
  }

  /*! LE operator for array splicing
   *
   * @param idx  Index, less than or equal to which will be included in
   *             subsequent splicing operations
   */
  splicer operator<=( index_t idx ){
    return splicer( std::less_equal<value_type>(), idx );
  }

  /*! Create an iterator to first element
   */
  iterator begin(){
    return Iterator( 0 );
  }

  /*! Create an iterator to final element
   */
  iterator end(){
    return Iterator( mSize );
  }

  /*! Create a const iterator to first element
   */
  const_iterator cbegin() const{
    return begin();
  }

  /*! Create a const iterator to final element
   */
  const_iterator cend() const{
    return end();
  }

  /*! Create iterator to specified element
   *
   * @param idx Index of element iterator will be directed to
   */
  iterator Iterator( index_t idx ){
    return iterator( &mArr[idx] );
  }
};

}

#endif

