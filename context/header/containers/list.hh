#pragma once

#include <allocator/std_wrapper.hh>

#include <list>

namespace flp::Contextual {

template<typename Type, typename Allocator = StdAllocWrapper<Type>>
  // requires Allocator is context aware
using List = std::list<Type, Allocator>;

}
