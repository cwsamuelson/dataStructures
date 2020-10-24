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

template<typename T>
class AverageCombiner{
public:
  template<typename Iter>
  auto operator()(Iter begin, Iter end){
    return std::accumulate(begin, end, T()) / std::distance(begin, end);
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

TEST_CASE("void/default combiner", "[combiners]"){
  event_trigger<int(int), default_combiner> trigger;
  auto& channel = *trigger.getChannel().lock();
  int counter = 0;
  channel.subscribe([&counter](auto a){ ++counter; return 42 + a; });
  channel.subscribe([&counter](auto a){ ++counter; return 12 + a; });

  trigger.fire(1);
  CHECK(std::is_same_v<decltype(trigger.fire(1)), void>);
  CHECK(counter == 2);
}

TEST_CASE("Average combiner", "[combiners]"){
  event_trigger<int(), AverageCombiner> trigger;
  auto& channel = *trigger.getChannel().lock();
  channel.subscribe([](){ return 6; });
  channel.subscribe([](){ return 12; });

  CHECK(trigger.fire() == 9);
}
