#pragma once

#include <allocator/std_wrapper.hh>

#include <vector>

namespace flp::Contextual {

template<typename Type, typename Allocator = StdAllocWrapper<Type>>
    // requires Allocator is context aware
using Vector = std::vector<Type, Allocator>;

}
