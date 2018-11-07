#ifndef __HASH_MAP_HH__
#define __HASH_MAP_HH__

#include<vector>
#include<tuple>
#include<optional>

#include<normal_iterator.hh>
#include<allocator_traits.hh>
#include<allocator.hh>

namespace gsw{

/*!
 *
 * @tparam KEY
 *
 * @tparam VALUE
 *
 * @tparam HASH
 *
 * @tparam ALLOC
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
  /*!
   */
  hash_map( size_t map_max = 16 )
    : mValues( map_max )
    , mMaxSize( map_max ){
  }

  /*!
   */
  template<typename U>
  hash_map( U&& other )
    : hash_map( other.mMaxSize ){
    mValues = std::forward<container>( other.mValues );
  }

  /*!
   */
  ~hash_map() = default;

  /*!
   *
   * @return
   */
  template<typename U>
  hash_map&
  operator=( U&& other ){
    mMaxSize = other.mMaxSize;
    mValues = std::forward<container>( other.mValues );

    return *this;
  }

  /*!
   */
  void
  insert( const key_type& key, const value_type& value ){
    mValues.at( mHashFunc( key ) % mMaxSize ) = {key, value};
  }

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
