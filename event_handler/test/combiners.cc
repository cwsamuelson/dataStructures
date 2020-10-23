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
