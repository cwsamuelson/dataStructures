#ifndef __MAP_HH__
#define __MAP_HH__

/*!
 * @example test-map.cc
 */

#include<algorithm>
#include<stdexcept>
#include<functional>
#include<utility>

#include<normal_iterator.hh>
#include<vector.hh>
#include<tuple.hh>

namespace gsw{

class keyNotFoundException : public std::out_of_range{
public:
  keyNotFoundException():
    std::out_of_range( "Requested key not found!" ){
  }
};

/*! 1:N associative container
 *
 * @tparam KEY Type used to find, store, reference data
 *
 * @tparam VALUE Type of data to be stored
 *
 * @tparam COMPARE Functor used to compare data of type KEY
 *
 * @tparam ALLOC type of allocator to use
 */
template<typename KEY, typename VALUE, typename COMPARE = std::less<KEY>, typename ALLOC = allocator<tuple<KEY, VALUE> > >
class map{
public:
  /*!
   */
  using key_type     = KEY;

  /*!
   */
  using map_type     = VALUE;

  /*!
   */
  using size_type    = unsigned long;

  /*!
   */
  using compare      = COMPARE;

  /*!
   */
  using storage_type = tuple<key_type, map_type>;

  /*!
   */
  using iterator     = normal_iterator<storage_type, map>;

  /*!
   */
  using alloc        = ALLOC;

private:
  vector<storage_type, alloc> mData;
  compare comparator;

  void normalize(){
    std::sort( mData.begin(), mData.end(),
      [&]( const storage_type& x, const storage_type& y )->bool{
        return comparator( get<0>( x ), get<0>( y ) );
      }
    );
  }
  
  size_type seek_index( const key_type& key ){
    size_type min = 0;
    size_type max = mData.size() - 1;
    size_type idx = ( max + min ) / 2.0;

    while( get<0>( mData[idx] ) != key ){
      if( min == max || idx >= mData.size() ){
        throw keyNotFoundException();
      }

      if( comparator( key, get<0>( mData[idx] ) ) ){
        max = idx - 1;
      } else {
        min = idx + 1;
      }

      idx = ( max + min ) / 2.0;
    }
    
    return idx;
  }

public:
  /*! Default ctor
   *
   * No data stored.
   */
  map( const alloc& alc = alloc() ):
    mData( 1, alc ){
  }

  /*! Copy ctor
   *
   * @tparam inputIter  Input iterator type
   *
   * @param first  first element of a range to be copied
   *
   * @param last  one past the end of the range of elements to be copied
   *
   * @param alc Allocator object to allocate data
   */
  template<class inputIter>
  map( inputIter first, inputIter last, const alloc& alc = alloc() ):
    mData( first, last, alc ){
    normalize();
  }

  /* Copy/move ctor
   *
   * @param other map to be copied/moved
   */
  template<typename U>
  map( U&& other, const alloc& alc = alloc() ):
    mData( alc ){
    mData = std::forward<U>( other.mData );
    comparator = other.comparator;
  }

  /*! Get reference associated with key
   *
   * @param key  index to find associated reference
   *
   * @return reference to found data
   *
   * Finds data associated with given key.  If no such exists, throws a
   * keyNotFoundException exception.
   */
  map_type& at( key_type key ){
    if( mData.empty() ){
      throw keyNotFoundException();
    }

    return get<1>( mData[seek_index( key )] );
  }

  /*! Get reference associated with key
   *
   * @param key  index key to find associated reference
   *
   * @return reference to found data
   *
   * Finds data associated with given key.  If no such exists, new data is
   * created.
   */
  map_type& operator[]( const key_type& key ){
    try{
      return at( key );
    } catch ( keyNotFoundException& ex ){
      emplace( key, map_type() );

      return at( key );
    }
  }

  /*! Get const reference associated with key
   *
   * @param key  index key to find associated reference
   *
   * @return reference to found data
   *
   * Finds data associated with given key.  If no such exists, new data is
   * created.
   */
  const map_type& operator[]( const key_type& key ) const{
    return ( *this )[key];
  }

  /*! Insert copies of new data
   *
   * @tparam inputIter  Input iterator type
   *
   * @param first  first element of a range to be copied
   *
   * @param last  one past the end of the range of elements to be copied
   */
  template<class inputIter>
  void insert( inputIter first, inputIter last ){
    for( ; first != last; ++first ){
      mData.push_back( *first );
    }

    normalize();
  }

  /*! Construct new object
   *
   * @tparam Args  template parameter pack of types to construct new object
   *
   * @param key  key to be associated with data
   *
   * @param args  arguments to construct new object
   *
   * @return iterator to new value
   *
   * @todo return correct iterator
   */
  template<class ...Args>
  iterator emplace( const key_type& key, Args ...args ){
    mData.emplace_back( key, map_type( std::forward<Args>( args )... ) );

    normalize();

    return mData.Iterator( seek_index( key ) );
  }

  /*! Get iterator to first element
   *
   * @return Iterator to beginning of container
   */
  iterator begin(){
    return mData.begin();
  }

  /*! Get constant iterator to first element
   *
   * @return Iterator to beginning of container
   */
  const iterator cbegin() const{
    return begin();
  }

  /*! Get iterator beyond container
   *
   * @return Iterator past end of container
   */
  iterator end(){
    return mData.end();
  }

  /*! Get constant iterator beyond container
   *
   * @return Iterator past end of container
   */
  const iterator cend() const{
    return end();
  }

  /*! Empty container of all data
   */
  void clear(){
    mData.clear();
  }

  /*! Check whether the container is empty or not
   *
   * @return Whether the container is empty
   */
  bool empty() const{
    return mData.empty();
  }

  /*! Get the number of elements in the container
   *
   * @return The number of elements in the container
   */
  size_type size() const{
    return mData.size();
  }
};

}

#endif

