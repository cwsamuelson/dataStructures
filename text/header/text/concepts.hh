#pragma once

#include <core/concepts.hh>
#include <text/support.hh>

namespace flp {

template<typename Type, typename CharT, typename Formatted>
concept Formatter =
  requires(const Type cformatter,
                 Type  formatter,
           const Formatted value,
           FormatParseContext<CharT> pcontext,
           FormatContext<CharT> fcontext) {
  { BoolConstant< formatter.parse(pcontext)>{} } -> SameAs<TrueType>;
  { BoolConstant<cformatter.format(value, fcontext)>{} } -> SameAs<TrueType>;
};

}
