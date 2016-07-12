#ifndef __STRING_HH__
#define __STRING_HH__

#include<basic_string.hh>

template<>
const char basic_string<char>::terminal = '\0';
typedef basic_string<char> string;


#endif

