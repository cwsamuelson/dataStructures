#pragma once

#include <type_traits>

namespace flp {

template<typename Type, bool IsConst>
using MaybeConst = std::conditional_t<IsConst, const Type, Type>;

}
