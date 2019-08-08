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
 *
 * @tparam T
 *
 * @todo Performance testing on array splicing.  may be a faster way to do this
 */
template<typename T>
struct splice_index{
  typedef std::function<bool( T, T )> opsig;

  opsig mOp;
  unsigned int mIdx;

  /*!
   *
   * @param op
   *
   * @param idx
   */
  splice_index( opsig op, unsigned int idx )
    : mOp( op )
    , mIdx( idx ){
  }
};

template<typename T>
struct splice_helper;

/*!
 *
 * @tparam T
 *
 * @tparam N
 */
template<typename T, unsigned int N>
struct splice_helper<T[N]>{
  array<T[N]>& mArr;
  std::vector<unsigned int> mIdxs;

  /*!
   * @param arr
   */
  splice_helper( array<T[N]>& arr )
    : mArr( arr ){
  }

  /*!
   * @param t
   */
  array<T[N]>&
  operator=( const T& t ){
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
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using array_t = T[N];
  using index_t = unsigned int;
  using splicer = splice_index<value_type>;
  using helper = splice_helper<value_type[N]>;
  using iterator = normal_iterator<value_type, array>;
  using const_iterator = const normal_iterator<value_type, array>;

  static constexpr index_t mSize = N;
  static constexpr unsigned int ptrdiff = sizeof( value_type );

private:
  array_t mArr;

public:
  /*! Default ctor
   */
  constexpr
  array() = default;
<<<<<<< HEAD:header/array.hh
=======

  constexpr
  array(array_t arr)
    : mArr(arr)
  {}
>>>>>>> master:array/array.hh

  /*! List initialization ctor
   *
   * @tparam ...Args
   *
   * @param args
   */
  template<typename ...Args>
  constexpr
  array( Args... args )
<<<<<<< HEAD:header/array.hh
    : mArr{ args...}{
  }
=======
    : mArr{ args...}
  {}
>>>>>>> master:array/array.hh

  /*! Get the size of the array
   *
   * @return The number of elements
   *
   * Returns the number of elements stored in the array.
   */
<<<<<<< HEAD:header/array.hh
  constexpr
  index_t
=======
  constexpr index_t
>>>>>>> master:array/array.hh
  size() const{
    return mSize;
  }

  /*! Indexing operator retrieves element at given index
   *
   * @param idx  Index at which value will be retrieved
   *
   * @todo a custom reference type could be used for array sub-assignment
   *       This will enable another weird syntax similar to the array splicing
   *       facilities. while splicing involves special splicing arrays to work,
   *       this would look simpler:
   *       the idea would look something like this:
   *  array<T, N> arr1;
   *  array<T, M> arr2;//where M<N
   *
   *  //do assignments/operations
   *
   *  arr1[X] = arr2;
   *
   *  REQUIRE( arr1[X] = arr2[0] );
   *  REQUIRE( arr1[X+1] = arr2[1] );
   *
   *       and the idea would work something like this:
   *  template<typename T>
   *  class arr_ref{
   *  private:
   *    T& data;
   *    int index;
   *
   *  public:
   *    operator& T(){
   *      return data;
   *    }
   *
   *    array
   *    operator=( const array<T, N>& rhs ){
   *      for( auto elem : rhs ){
   *        // do assignment starting at index this is a reference to
   *      }
   *    }
   *  }
   */
  reference
  operator[]( index_t idx ){
    return mArr[idx];
  }

  /*! Index operator overload for const correctness
   *
   * @param idx  Index at which value will be retrieved
   *
   * Behaves the same as non-const version, but provides a const reference,
   * and can be used on const objects.
   */
<<<<<<< HEAD:header/array.hh
  constexpr
  const_reference
=======
  constexpr const_reference
>>>>>>> master:array/array.hh
  operator[]( index_t idx ) const{
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
  helper
  operator[]( const splicer& spl ){
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
  helper
  operator[]( array<unsigned int[M]>& a ){
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
  splicer
  operator>( index_t idx ){
    return splicer( std::greater<value_type>(), idx );
  }

  /*! GE operator for array splicing
   *
   * @param idx  Index, greater than and equal to which will be included in
   *             subsequent splicing operations
   */
  splicer
  operator>=( index_t idx ){
    return splicer( std::greater_equal<value_type>(), idx );
  }

  /*! LT operator for array splicing
   *
   * @param idx  Index, lesser than which will be included in subsequent
   *             splicing operations
   */
  splicer
  operator<( index_t idx ){
    return splicer( std::less<value_type>(), idx );
  }

  /*! LE operator for array splicing
   *
   * @param idx  Index, less than or equal to which will be included in
   *             subsequent splicing operations
   */
  splicer
  operator<=( index_t idx ){
    return splicer( std::less_equal<value_type>(), idx );
  }

  /*! Create an iterator to first element
   */
  iterator
  begin(){
    return Iterator( 0 );
  }

  /*! Create an iterator to final element
   */
  iterator
  end(){
    return Iterator( mSize );
  }

  /*! Create a const iterator to first element
   */
  const_iterator
  cbegin() const{
    return begin();
  }

  /*! Create a const iterator to final element
   */
  const_iterator
  cend() const{
    return end();
  }

  /*! Create iterator to specified element
   *
   * @param idx Index of element iterator will be directed to
   */
  iterator
  Iterator( index_t idx ){
    return iterator( &mArr[idx] );
  }
};

}

#endif
