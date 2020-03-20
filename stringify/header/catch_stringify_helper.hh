#ifndef __STRINGIFY_HELPER_HH__
#define __STRINGIFY_HELPER_HH__

#include <string>
#include <set>

// define how to stringify a set for catch error printing
namespace Catch {
  /*template<typename T, typename Compare, typename Allocator>
  struct StringMaker<std::set<T, Compare, Allocator>> {
      static std::string convert(const std::set<T, Compare, Allocator>& s) {
        return ::Catch::Detail::rangeToString(s.begin(), s.end());
      }
  };*/
}

template<typename OSTREAM, typename T, typename Compare, typename Allocator>
OSTREAM& operator<<(OSTREAM& os, const std::set<T, Compare, Allocator>& s) {
  return os << ::Catch::Detail::rangeToString(s.begin(), s.end());
}

}

#endif
