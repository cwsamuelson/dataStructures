#pragma once

#include <allocator/std_wrapper.hh>

#include <string>

namespace flp::Contextual {

// basic_string
template<typename Char, typename Traits = std::char_traits<Char>, typename Allocator = StdAllocWrapper<Char>>
    // requires Allocator is context aware
using BasicString = std::basic_string<Char, Traits, Allocator>;

using String = BasicString<char>;

//using WString = BasicString<wchar>;

}
