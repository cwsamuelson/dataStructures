#pragma once

#include <print>
#include <tuple>
#include <utility>

namespace flp {

template<typename Function, typename ...Args>
void static_loop(Function&& function, Args&& ...args) {
  (function(args), ...);
}

template<typename Function, typename T, typename ...Args, T ...Ts>
void tuple_loop_impl(Function&& function, const std::tuple<Args...>& tuple, std::integer_sequence<T, Ts...>) {
  (function(std::get<Ts>(tuple)), ...);
}

template<typename Function, typename ...Args>
void tuple_loop(Function&& function, const std::tuple<Args...>& tuple) {
  tuple_loop_impl(function, tuple, std::make_index_sequence<sizeof...(Args)>());
}

/*int main() {
    StaticLoop([](const auto& x) {
        std::println("{}", x);
    }, 42, 1138, "xxx");

    TupleLoop([](const auto& x) {
        std::println("{}", x);
    }, std::make_tuple(42, 1138, "xxx"));
}*/

}
