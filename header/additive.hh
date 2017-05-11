#ifndef __ADDITIVE_HH__
#define __ADDITIVE_HH__

template<typename LHS, typename RHS = LHS>
class additive{
public:
  typedef LHS lhs_type;
  typedef RHS rhs_type;

  friend lhs_type operator+( lhs_type t, const rhs_type& u ) noexcept{
    return ( t += u );
  }
  friend lhs_type operator-( lhs_type t, const rhs_type& u ) noexcept{
    return ( t -= u );
  }
};

#endif

