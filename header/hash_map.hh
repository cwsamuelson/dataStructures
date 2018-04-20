#ifndef __HASH_MAP_HH__
#define __HASH_MAP_HH__

#include<vector>
#include<tuple>

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
  using container = std::vector<storage_type>;

  container mValues;
  hash_fn mHashFunc;

public:
  /*!
   */
  hash_map() = default;

  /*!
   */
  template<typename U>
  hash_map( U&& other )
    : mValues( std::forward<container>( other.mValues ) ){
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
    mValues = std::forward<container>( other.mValues );

    return *this;
  }

  /*!
   */
  void
  insert( const key_type& key, const value_type& value ){
    mValues[mHashFunc( key )] = {key, value};
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
    return std::get<0>( mValues[mHashFunc( key )] );
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
    return mValues.empty();
  }

  /*!
   *
   * @return
   */
  size_t
  size() const{
    return mValues.size();
  }
};

}

#endif

