#pragma once

#include <allocator/std_wrapper.hh>

#include <deque>

namespace flp::Contextual {

template<typename Type, typename Allocator = StdAllocWrapper<Type>>
    // requires Allocator is context aware
using Deque = std::deque<Type, Allocator>;

}
