#pragma once

#include <dimension.hh>
#include <system.hh>

namespace flp {

//! @TODO conditional noexcept
template<std::derived_from<Dimension> dimension, std::derived_from<System> system>
class Unit {
};

} // namespace flp

