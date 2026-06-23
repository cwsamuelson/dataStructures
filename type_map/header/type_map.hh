#pragma once


namespace flp {

template<typename Type, auto Value>
struct TVPair {};

template<TVPair ...Pairs>
struct TypeMap {
};

} // namespace flp
