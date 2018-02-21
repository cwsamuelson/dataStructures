#ifndef __HASH_MAP_HH__
#define __HASH_MAP_HH__

#include<vector>

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
template<typename KEY, typename VALUE, typename HASH = std::hash<KEY>, typename ALLOC = allocator<> >
class hash_map{
public:
  using key_type = KEY;
  using value_type = VALUE;
  using iterator = ;
  using hash_fn = HASH;

private:
  using container = std::vector<value_type>;

  container mValues;
  hash_fn mHashFunc;

public:
  /*!
   */
  hash_map() default;

  /*!
   */
  template<typename U>
  hash_map( U&& other )
    : mValues( std::forward<container>( other.mValues ){
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
    mValues[mHashFunc( key )] = value;
  }

  /*!
   */
  template<typename ...ARGS>
  void
  emplace( const key_type&, ARGS ...args )

  /*!
   *
   * @param key
   *
   * @return
   */
  value_type&
  operator[]( const key_type& key ){
    return mValues[mHashFunc( key )];
  }

  /*!
   *
   * @return
   */
  iterator
  begin()

  /*!
   *
   * @return
   */
  iterator
  end()

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

