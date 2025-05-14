#pragma once

#include <allocator/std_wrapper.hh>

#include <forward_list>

namespace flp::Contextual {

template<typename Type, typename Allocator = StdAllocWrapper<Type>>
  // requires Allocator is context aware
using ForwardList = std::forward_list<Type, Allocator>;

}
