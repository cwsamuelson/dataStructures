#include <event_handler.hh>

#include <catch2/catch.hpp>

#include <vector>

using namespace gsw;

template <typename T>
class AggregateCombiner{
public:
  template<typename Iter>
  std::vector<T> operator()(Iter begin, Iter end){
    return {begin, end};
  }
};

template<typename T>
class MaximumCombiner{
public:
  template<typename Iter>
  T operator()(Iter begin, Iter end){
    return *std::max_element(begin, end);
  }
};

template<typename T>
class SumCombiner{
public:
  template<typename Iter>
  decltype(std::declval<T>() + std::declval<T>()) operator()(Iter begin, Iter end){
    return std::accumulate(begin, end, T());
  }
};

TEST_CASE("Aggregate combiner", "[combiners]"){
  event_trigger<int(), AggregateCombiner> trigger;
  auto& channel = *trigger.getChannel().lock();
  channel.subscribe([]()->int{ return 42; });
  channel.subscribe([]()->int{ return 24; });

  auto results = trigger.fire();
  REQUIRE(results.size() == 2);
  CHECK(results[0] == 42);
  CHECK(results[1] == 24);
}

TEST_CASE("Maximum combiner", "[combiners]"){
  event_trigger<int(), MaximumCombiner> trigger;
  auto& channel = *trigger.getChannel().lock();
  channel.subscribe([]()->int{ return 42; });
  channel.subscribe([]()->int{ return 24; });

  CHECK(trigger.fire() == 42);
}

TEST_CASE("Sum combiner", "[combiners]"){
  event_trigger<int(), SumCombiner> trigger;
  auto& channel = *trigger.getChannel().lock();
  channel.subscribe([](){ return 42; });
  channel.subscribe([](){ return 12; });

  CHECK(trigger.fire() == 54);
}
