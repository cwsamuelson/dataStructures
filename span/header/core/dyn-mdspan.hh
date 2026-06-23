#pragma once

#include "core/mdspan.hh"

namespace flp {

template<
  typename Type,
  LayoutPolicy Layout = DefaultLayout,
  AccessPolicy Accessor = DefaultAccessor
>
struct MDSpan<Type, DynamicExtents, Layout, Accessor> {
  Type* data_handle;
};

}
