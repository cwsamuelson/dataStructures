#ifndef __ALGORITHM_HH__
#define __ALGORITHM_HH__

/*!
 * @example test-algorithm.cc
 */

#include<vector.hh>

namespace gsw{

/*! Invokes member function pointer
 *
 * @tparam OBJ  Type of object which member function will act on
 *
 * @tparam MEMBER_FN  Type of member function pointer
 *
 * @tparam ...Args  Type pack of argument types
 *
 * @param obj  Object to run memfun on
 *
 * @param memfun  Member function to be run
 *
 * @param ...args  Arguments to be sent to function
 *
 * @return Whatever type or result comes from memfun
 *
 * Invokes a member function pointer of the form:
 * class foo{
 * public:
 *   return_type ( foo::*MemFnPtr ) (  Args ...args  );
 * };
 */
template<typename OBJ, typename MEMBER_FN, typename ...Args>
auto invoke(  OBJ obj, MEMBER_FN memfun, Args ...args  ){
  return (  obj.*memfun  )(  args...  );
}

/*! Less than operator functor
 *
 * @tparam T  Type to be compared
 */
template<typename T>
struct less{
  /*!
   */
  bool operator()( const T& lhs, const T& rhs ){
    return lhs < rhs;
  }
};

template<typename iter>
unsigned long distance( iter first, iter last ){
  unsigned long ret = 0;

  while( first++ != last ){
    ++ret;
  }

  return ret;
}

template<typename iter>
void myswap( iter x, iter y ){
  auto z = *x;
  *x = *y;
  *y = z;
}

template<typename iter, typename compare>
void merge( iter first, iter mid, iter last, compare comp ){
  vector<typename iter::value_type> vec;
  auto middle = mid;
  auto start = first;
  auto stop = last;

  while( first != middle && mid != last ){
    if( comp( *mid, *first ) ){
      vec.push_back( *mid );
      ++mid;
    } else {
      vec.push_back( *first );
      ++first;
    }
  }
  while( first != middle ){
    vec.push_back( *( first++ ) );
  }
  while( mid != last ){
    vec.push_back( *( mid++ ) );
  }

  auto begin = vec.begin();
  for( ;start != stop; ++start, ++begin ){
    *start = *begin;
  }
}

template<typename iter, typename compare = less<typename iter::value_type> >
void sort( iter first, iter last, compare comp = compare() ){
  auto length = distance( first, last );

  if( length < 2 ){
    return;
  }

  auto mid = first + ( length / 2 );
  sort( first, mid, comp );
  sort( mid, last, comp );

  merge( first, mid, last, comp );
}

}

#endif

