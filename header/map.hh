#ifndef __MAP_HH__
#define __MAP_HH__

#include<algorithm>
#include<exception>
#include<functional>
#include<utility>

#include<normal_iterator.hh>
#include<vector.hh>
#include<tuple.hh>

class keyNotFoundException : public std::exception{
public:
  virtual const char* what() const noexcept{
    return "Requested key not found!";
  }
};

template<class KEY, class VALUE, class COMPARE = std::less<KEY> >
class map{
public:
  typedef KEY key_type;
  typedef VALUE map_type;
  typedef unsigned long size_type;
  typedef COMPARE compare;
  typedef tuple<key_type, map_type> storage_type;
  typedef normal_iterator<storage_type, map> iterator;

private:
  vector<storage_type> mData;
  compare comparator;

  void normalize(){
    std::sort( mData.begin(), mData.end(),
      [&]( const storage_type& x, const storage_type& y )->bool{
        return comparator( get<0>( x ), get<0>( y ) );
      }
     );
  }

public:
  /*!
   * @brief default ctor
   *
   * No data stored.
   */
  map() = default;

  /*!
   * @brief copy ctor
   *
   * @tparam inputIter  Input iterator type
   *
   * @param first  first element of a range to be copied
   *
   * @param last  one past the end of the range of elements to be copied
   */
  template<class inputIter>
  map( inputIter first, inputIter last ):
    mData( first, last ){
    normalize();
  }

  /*!
   * @brief copy ctor
   *
   * @param other  map to be copied
   */
  map( const map& other ){
    mData = other.mData;
    comparator = other.comparator;
  }

  /*!
   * @brief move ctor
   *
   * @param other  map to be moved here
   */
  map( map&& other ){
    mData = std::forward<decltype( mData )>( other.mData );
    comparator = other.comparator;
  }


  /*!
   * @brief get reference associated with key
   *
   * @param key  index key to find associated reference
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

    unsigned int idx;
    unsigned int min = 0;
    unsigned int max = mData.size() - 1;

    idx = ( max + min ) / 2.0;

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
    return get<1>( mData[idx] );
  }

  /*!
   * @brief get reference associated with key
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
      mData.emplace_back( key, map_type() );
      normalize();

      return at( key );
    }
  }

  /*!
   * @brief get const reference associated with key
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

  /*!
   * @brief Insert copies of new data
   *
   * @tparam inputIter  Input iterator type
   *
   * @param first  first element of a range to be copied
   *
   * @param last  one past the end of the range of elements to be copied
   */
  template<class inputIter>
  void insert( inputIter first, inputIter last ){
    for( ;first != last; ++first ){
      mData.push_back( *first );
    }
    normalize();
  }

  /*!
   * @brief construct new object
   *
   * @tparam Args  template parameter pack of types to construct new object
   *
   * @param key  key to be associated with data
   *
   * @param args  arguments to construct new object
   *
   * @return iterator to new value
   */
  template<class ...Args>
  iterator emplace( const key_type& key, Args ...args ){
    mData.emplace_back( key, map_type( std::forward<Args>( args )... ) );
    normalize();
    //TODO: return correct iterator
  }

  /*!
   * @brief
   *
   * @return
   */
  iterator begin(){
    return mData.begin();
  }

  /*!
   * @brief
   *
   * @return
   */
  const iterator cbegin() const{
    return begin();
  }

  /*!
   * @brief
   *
   * @return
   */
  iterator end(){
    return mData.end();
  }

  /*!
   * @brief
   *
   * @return
   */
  const iterator cend() const{
    return end();
  }

  /*!
   * @brief
   */
  void clear(){
    mData.clear();
  }

  /*!
   * @brief
   *
   * @return
   */
  bool empty() const{
    return mData.empty();
  }

  /*!
   * @brief
   *
   * @return
   */
  size_type size() const{
    return mData.size();
  }
};

#endif

