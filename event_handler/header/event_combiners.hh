#ifndef GALACTICSTRUCTURES_EVENT_COMBINERS_HH
#define GALACTICSTRUCTURES_EVENT_COMBINERS_HH

#include <event_handler.hh>

#include <numeric>

namespace gsw{

template <typename T>
class AggregateCombiner{
public:
  using result_type = std::vector<T>;

  template<typename Iter>
  std::vector<T> operator()(Iter begin, Iter end){
    return {begin, end};
  }
};

template<typename T>
class MaximumCombiner{
public:
  using result_type = T;

  template<typename Iter>
  T operator()(Iter begin, Iter end){
    return *std::max_element(begin, end);
  }
};

template<typename T>
class SumCombiner{
public:
  using result_type = decltype(std::declval<T>() + std::declval<T>());

  template<typename Iter>
  decltype(std::declval<T>() + std::declval<T>()) operator()(Iter begin, Iter end){
    return std::accumulate(begin, end, T());
  }
};

template<typename T>
class AverageCombiner{
public:
  using result_type = decltype(std::declval<T>() + std::declval<T>());

  template<typename Iter>
  auto operator()(Iter begin, Iter end){
    if constexpr (std::is_floating_point_v<T>) {
      return std::accumulate(begin, end, 0.0) / std::distance(begin, end);
    } else {
      return std::accumulate(begin, end, T()) / std::distance(begin, end);
    }
  }
};

}

#endif //GALACTICSTRUCTURES_EVENT_COMBINERS_HH
