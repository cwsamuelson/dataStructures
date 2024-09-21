#include <producer_consumer.hpp>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Producer consumer tests") {
  auto [producer, consumer] = create_spsc<int, SimpleStore_st<int>>();
  CHECK(consumer.empty());
  CHECK(consumer.size() == 0);
  CHECK(consumer.running());
  CHECK(not consumer.pop().has_value());

  CHECK(producer.empty());
  CHECK(consumer.size() == 0);
  CHECK(producer.running());
  CHECK(not producer.pop().has_value());

  producer.push(1138);

  CHECK(not consumer.empty());
  CHECK(consumer.size() == 1);
  CHECK(consumer.running());

  CHECK(not producer.empty());
  CHECK(consumer.size() == 1);
  CHECK(producer.running());

  CHECK(consumer.pop().has_value());
  CHECK(not producer.pop().has_value());

  producer.push(42);
  CHECK(*consumer.pop() == 42);
}

