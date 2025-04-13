#pragma once


namespace flp {

template<typename ReturnT, typename ...Args>
struct Function;

template<typename ReturnT, typename ...Args>
struct Function<ReturnT(Args...)> {
};

} // namespace flp

