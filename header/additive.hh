#ifndef __ADDITIVE_HH__
#define __ADDITIVE_HH__

/*!
 * @example test-operators.cc
 */

namespace gsw{

/*! Additive utility class to provide addition and subtraction operators
 *
 * @tparam LHS  Type of the left hand side of the + and - operators
 *
 * @tparam RHS  Type of the right hand side of the + and - operators
 *
 * Convenience class to simply allow the + and - operators to a class
 * implementing the += and -= operators through inheritance.
 *
 * Intended usage:
 * @code{.cpp}
 * class foo : public additive<foo>{
 * private:
 *   int x;
 *
 * public:
 *   friend foo& operator+=( foo& lhs, const foo& rhs ){
 *     lhs.x += rhs.x;
 *
 *     return lhs;
 *   }
 *   friend foo& operator-=( foo& lhs, const foo& rhs ){
 *     lhs.x -= rhs.x;
 *
 *     return lhs;
 *   }
 * };
 * @endcode
 *
 * This will provide 'for free' the + and - operators as well.
 */
template<typename LHS, typename RHS = LHS>
class additive{
public:
  using lhs_type = LHS;
  using rhs_type = RHS;

  /*! Addition operator
   *
   * @param lhs  Left hand side of + operator
   *
   * @param rhs  Right hand side of + operator
   *
   * @return Value of result of the addition
   *
   * Adds together lhs and rhs using the += operator of the derived class.
   */
  constexpr friend auto operator+( lhs_type lhs, const rhs_type& rhs ) noexcept{
    return ( lhs += rhs );
  }

  /*! Subtraction operator
   *
   * @param lhs  Left hand side of - operator
   *
   * @param rhs  Right hand side of - operator
   *
   * @return Value of result of the subtraction
   *
   * Subtracts rhs from lhs using the -= operator of the derived class.
   */
  constexpr friend auto operator-( lhs_type lhs, const rhs_type& rhs ) noexcept{
    return ( lhs -= rhs );
  }
};

}

#endif

