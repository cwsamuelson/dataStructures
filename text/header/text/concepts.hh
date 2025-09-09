#pragma once

#include <core/concepts.hh>
#include "text/support.hh"

namespace flp {

template<typename Formatter, typename Type>
concept ConstexprFormatter =
  requires(const Formatter cformatter, Formatter formatter, const Type value, FormatParseContext pcontext, FormatContext fcontext) {
  { BoolConstant< formatter.parse(pcontext)>{} } -> SameAs<TrueType>;
  { BoolConstant<cformatter.format(value, fcontext)>{} } -> SameAs<TrueType>;
};

}
