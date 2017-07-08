#ifndef __STRING_HH__
#define __STRING_HH__

/*!
 * @example test-string.cc
 */

#include<basic_string.hh>

namespace gsw{

template<>
const char basic_string<char>::terminal = '\0';

typedef basic_string<char> string;

}

#endif

