#ifndef __ADDITIVE_HH__
#define __ADDITIVE_HH__

/*!
 * @example test-operators.cc
 */

namespace gsw{

/*! Comparison utility class to provide comparison operators
 *
 * @tparam LHS  Type of the left hand side of the comparison operators
 *
 * @tparam RHS  Type of the right hand side of the comparison operators
 *
 * Convenience class to simply allow the !=, >=, >, <= operators to a class
 * implementing the == and < operators through inheritance.
 *
 * Intended usage:
 * @code{.cpp}
 * class foo : public comparitive<foo>{
 * private:
 *   int x;
 *
 * public:
 *   friend bool operator<( const foo& lhs, const foo& rhs ){
 *     return lhs.x < rhs.x;
 *   }
 *   friend bool operator==( const foo& lhs, const foo& rhs ){
 *     return lhs.x == rhs.x;
 *   }
 * };
 * @endcode
 *
 * This will provide 'for free' the !=, >=, >, and <= operators as well.
 */
template<typename LHS, typename RHS = LHS>
class comparitive{
public:
  typedef LHS lhs_type;
  typedef RHS rhs_type;

  /*! Non-equality comparison operator
   *
   * @param lhs Left hand side of != operator
   *
   * @param rhs Right hand side of != operator
   *
   * @return Whether lhs != rhs
   */
  constexpr friend bool operator!=( const lhs_type& lhs, const rhs_type& rhs ) noexcept{
    return !( lhs == rhs );
  }

  /*! Greater than comparison operator
   *
   * @param lhs Left hand side of > operator
   *
   * @param rhs Right hand side of > operator
   *
   * @return Whether lhs > rhs
   */
  constexpr friend bool operator>( const lhs_type& lhs, const rhs_type& rhs ) noexcept{
    return !( lhs <= rhs );
  }

  /*! Greater than or equal comparison operator
   *
   * @param lhs Left hand side of >= operator
   *
   * @param rhs Right hand side of >= operator
   *
   * @return Whether lhs >= rhs
   */
  constexpr friend bool operator>=( const lhs_type& lhs, const rhs_type& rhs ) noexcept{
    return !( lhs < rhs );
  }

  /*! Less than or equal comparison operator
   *
   * @param lhs Left hand side of <= operator
   *
   * @param rhs Right hand side of <= operator
   *
   * @return whether lhs is <= rhs
   */
  constexpr friend bool operator<=( const lhs_type& lhs, const rhs_type& rhs ) noexcept{
    return ( lhs < rhs ) || ( lhs == rhs );
  }
};

}

#endif

