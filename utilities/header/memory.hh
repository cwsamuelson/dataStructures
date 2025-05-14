#pragma once

#include <boost/shared_ptr.hpp>

#include <memory>

namespace flp {

template<typename Type>
[[maybe_unused]]
boost::shared_ptr<Type> make_shared_ptr(std::shared_ptr<Type>& ptr) {
  return boost::shared_ptr<Type>(ptr.get(), [ptr](Type*) mutable {
    ptr.reset();
  });
}

template<typename Type>
[[maybe_unused]]
std::shared_ptr<Type> make_shared_ptr(boost::shared_ptr<Type>& ptr) {
  return std::shared_ptr<Type>(ptr.get(), [ptr](Type*) mutable {
    ptr.reset();
  });
}

} // namespace flp

