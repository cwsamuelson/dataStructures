#pragma once

namespace flp {

// The idea is that a delegate is lighter weight than something as flexible as `std::function`
// It should not be confused to substitute for such, and does not provide the same feature set

// The idea was mostly inspired from:
// https://github.com/skypjack/entt/blob/master/docs/md/signal.md

template<typename ReturnT, typename ...Args>
struct Delegate;

template<typename ReturnT, typename ...Args>
struct Delegate<ReturnT(Args...)> {
};

} // namespace flp

