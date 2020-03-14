#ifndef __STRINGIFY_HELPER_HH__
#define __STRINGIFY_HELPER_HH__

// define how to stringify a set for catch error printing
namespace Catch {

template<typename T, typename compare, typename Allocator>
struct StringMaker<std::set<T, compare, Allocator>> {
  static std::string convert(std::set<T, compare, Allocator> const& s) {
    return ::Catch::Detail::rangeToString(s.begin(), s.end());
  }
};

}

#endif
