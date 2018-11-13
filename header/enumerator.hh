#ifndef __ENUMERATOR_HH__
#define __ENUMERATOR_HH__

#include<type_traits>
#include<utility>

template<typename container_t>
class enumerator{
public:
  using iterator_type  = std::conditional_t<std::is_const_v<container_t>,
                                          typename container_t::const_iterator,
                                          typename container_t::iterator>;
  using pointer_type   = std::conditional_t<std::is_const_v<container_t>,
                                          typename container_t::const_pointer,
                                          typename container_t::pointer>;
  using reference_type = std::conditional_t<std::is_const_v<container_t>,
                                          typename container_t::const_reference,
                                          typename container_t::reference>;

  class enumerator_iter{
  public:
    size_t mIndex;
    iterator_type mIter;

    constexpr
    auto
    operator++(){
      ++mIndex;
      ++mIter;

      return *this;
    }

    constexpr
    bool
    operator!=( const iterator_type& iter ) const{
      return mIter != iter;
    }

    constexpr
    std::pair<size_t, reference_type>
    operator*(){
      return {mIndex, *mIter};
    }
  };

private:
  container_t& mContainer;

public:
  constexpr
  enumerator( container_t& c )
    : mContainer( c ){
  }

  constexpr
  enumerator_iter
  begin(){
    return {0, std::begin( mContainer )};
  }

  constexpr
  auto
  end(){
    return std::end( mContainer );
  }
};

template<typename container_t>
constexpr
auto
enumerate( container_t& c ){
  return enumerator( c );
}

#endif
