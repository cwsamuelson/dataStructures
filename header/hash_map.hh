#ifndef __HASH_MAP_HH__
#define __HASH_MAP_HH__

#include<vector>
#include<tuple>
#include<optional>

#include<normal_iterator.hh>
#include<allocator_traits.hh>
#include<allocator.hh>

namespace gsw{

/*! Associative data container type
 *
 * @tparam KEY Input type, used to retrieve output VALUE type objects
 *
 * @tparam VALUE Output/'stored' type, found/referenced using the KEY type
 *
 * @tparam HASH Type used to hash KEY for easier storage, and data locating
 *
 * @tparam ALLOC Type used to allocate key-value pairs
 */
template<typename KEY, typename VALUE, typename HASH = std::hash<KEY>, typename ALLOC = allocator<std::tuple<KEY, VALUE> > >
class hash_map{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using storage_type = std::tuple<key_type, value_type>;
  using iterator = normal_iterator<storage_type, hash_map>;
  using hash_fn = HASH;

private:
  using container = std::vector<std::optional<storage_type> >;

  container mValues;
  hash_fn mHashFunc;
  size_t mMaxSize;

public:
  /*! Ctor defining the number of buckets to be hashed into
   *
   * @param map_max Maximum number of buckets
   */
  hash_map( size_t map_max = 16 )
    : mValues( map_max )
    , mMaxSize( map_max ){
  }

  /*! Move constructor
   *
   * @param other
   */
  template<typename U>
  hash_map( U&& other )
    : hash_map( other.mMaxSize ){
    mValues = std::forward<container>( other.mValues );
  }

  /*! Destructor
   */
  ~hash_map() = default;

  /*! Universal reference assignment
   *
   * @param other Object to be moved/copied
   *
   * @return Resulting *this
   */
  template<typename U>
  hash_map&
  operator=( U&& other ){
    mMaxSize = other.mMaxSize;
    mValues = std::forward<container>( other.mValues );

    return *this;
  }

  /*! Insert a new key-value pair
   *
   * @param key Key to new value being inserted
   *
   * @param value Value being inserted
   */
  void
  insert( const key_type& key, const value_type& value ){
    mValues.at( mHashFunc( key ) % mMaxSize ) = {key, value};
  }

  /*! Erase data already in container
   *
   * @param key key to find value to erase from container
   */
  void
  erase( const key_type& key ){
    mValues.at( mHashFunc( key ) % mMaxSize ).reset();
  }

  /*!
   */
  template<typename ...ARGS>
  void
  emplace( const key_type&, ARGS ...args ){}

  /*!
   *
   * @param key
   *
   * @return
   */
  value_type&
  operator[]( const key_type& key ){
    auto hash = mHashFunc( key );
    auto idx = hash % mMaxSize;

    if( !mValues.at( idx ) ){
      mValues.at( idx ) = {key, value_type{}};
    }

    return std::get<0>( mValues.at( idx ).value() );
  }

  /*!
   *
   * @return
   */
  iterator
  begin(){
  }

  /*!
   *
   * @return
   */
  iterator
  end(){
  }

  /*!
   *
   * @return
   */
  bool
  empty() const{
    for( const auto& it : mValues ){
      if( it ){
        return false;
      }
    }

    return true;
  }

  /*!
   *
   * @return
   */
  size_t
  size() const{
    size_t count = 0;

    for( const auto& it : mValues ){
      if( it ){
        ++count;
      }
    }

    return count;
  }
};

}

#endif
