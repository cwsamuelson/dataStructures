#ifndef __ENUMERATOR_HH__
#define __ENUMERATOR_HH__

#include<type_traits>
#include<utility>

/*!
 * @example test-enumerator.cc
 */

namespace gsw {

/*! Container wrapper that provides iterators with counters
 *
 * @tparam container_t type of container to enumerate
 *
 * enumerator wraps a container class, and provides special begin/end methods,
 * as well as providing a special iterator wrapper.  The primary function of
 * this class is to provide functionality as:
 * for( auto [i, iter] : enumerate( container ) ){...}
 * where i is a counter/index, and iter is a reference to an object obtained by
 * dereferencing the underlying iterator.
 */
template<typename container_t>
class enumerator {
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

  /*! Iterator wrapper
   *
   * Helper class that forwards increment, comparison, and deref calls to the
   * underlying object, and provides an index/counter as well.
   */
  class enumerator_iter {
  public:
    size_t mIndex;
    iterator_type mIter;

    /*! Increment underlying iterator and counter
     *
     * @return Reference to modified iter
     */
    constexpr auto operator++() {
      ++mIndex;
      ++mIter;

      return *this;
    }

    /*! Iterator comparison
     *
     * @param iter Another iterator to compare to
     *
     * @return Whether this is not-equal to iter
     */
    constexpr bool operator!=(const iterator_type& iter) const {
      return mIter != iter;
    }

    /*! Iterator dereference
     *
     * @return Pair of counter and reference to dereffed iterator
     */
    constexpr std::pair<size_t, reference_type> operator*() {
      return { mIndex, *mIter };
    }
  };

private:
  container_t& mContainer;

public:
  /*! Enumerator constructor
   *
   * @param c Refrence to container to wrap
   */
  constexpr enumerator(container_t& c)
          : mContainer(c) {
  }

  /*! Get beginning iterator
   *
   * @return Iterator wrapper providing access to underlying container
   */
  constexpr enumerator_iter begin() {
    return { 0, std::begin(mContainer) };
  }

  /*! Get ending iterator
   *
   * @return Iterator wrapper providing access to underlying end.
   */
  constexpr auto end() {
    return std::end(mContainer);
  }
};

/*! Helper function to create an enumerator
 *
 * @tparam container_t Type of container to be wrapped
 *
 * @param c Reference to container that will be wrapped
 *
 * @return Container wrapper whose iterators will provide access to c
 */
template<typename container_t>
constexpr auto enumerate(container_t& c) {
  return enumerator(c);
}

}

#endif
