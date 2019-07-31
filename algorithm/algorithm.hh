#ifndef __ALGORITHM_HH__
#define __ALGORITHM_HH__

#include<algorithm>
#include<cmath>

/*!
 * @example test-algorithm.cc
 */

//#include<vector.hh>

namespace gsw{

/*! Floating point comparator algorithm
 *
 * @tparam T Floating point type to be compared
 *
 * @param f1 First value to be compared against f2
 *
 * @param f2 Second value to be compared against f1
 *
 * @return The effective equality of f1 and f2
 *
 * Due to the nature of the floating point implementation if
 * a==b and b==c a might== c.  To account for this, a more rigorous comparison
 * must be utilized.
 */
template<typename T>
static bool are_equal( T f1, T f2 ){
  return ( std::fabs( f1 - f2 ) <= std::numeric_limits<T>::epsilon() * std::max( {1.0, std::fabs( f1 ), std::fabs( f2 )} ) );
}

template<>
bool are_equal<float>( float f1, float f2 ){
  return ( std::fabs( f1 - f2 ) <= std::numeric_limits<float>::epsilon() * std::max( {1.0f, std::fabs( f1 ), std::fabs( f2 )} ) );
}

/*! Invokes member function pointer
 *
 * @tparam OBJ Type of object which member function will act on
 *
 * @tparam MEMBER_FN Type of member function pointer
 *
 * @tparam ...Args Type pack of argument types
 *
 * @param obj Object to run memfun on
 *
 * @param memfun Member function to be run
 *
 * @param ...args Arguments to be sent to function
 *
 * @return Whatever type or result comes from memfun
 *
 * Invokes a member function pointer of the form:
 * class foo{
 * public:
 *   return_type ( foo::*MemFnPtr ) ( Args ...args );
 * };
 */
template<typename OBJ, typename MEMBER_FN, typename ...Args>
auto invoke( OBJ obj, MEMBER_FN memfun, Args ...args ){
  return ( obj.*memfun )( args... );
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
void swap( iter x, iter y ){
  auto z = *x;
  *x = *y;
  *y = z;
}

/*template<typename iter, typename compare>
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
*/
}

#endif

