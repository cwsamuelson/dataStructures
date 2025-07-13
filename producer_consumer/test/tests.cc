#include <producer_consumer.hpp>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("producer-consumer single") {
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

TEST_CASE("producer-consumer multiple") {
  auto [pspawner, cspawner] = create_mpmc<int, SimpleStore_st<int>>();

  auto producer1 = pspawner.spawn();
  auto consumer1 = cspawner.spawn();
  auto producer2 = pspawner.spawn();
  auto consumer2 = cspawner.spawn();

  CHECK(consumer1.empty());
  CHECK(consumer1.size() == 0);
  CHECK(consumer1.running());
  CHECK(not consumer1.pop().has_value());

  CHECK(producer1.empty());
  CHECK(consumer1.size() == 0);
  CHECK(producer1.running());
  CHECK(not producer1.pop().has_value());

  CHECK(consumer2.empty());
  CHECK(consumer2.size() == 0);
  CHECK(consumer2.running());
  CHECK(not consumer2.pop().has_value());

  CHECK(producer2.empty());
  CHECK(consumer2.size() == 0);
  CHECK(producer2.running());
  CHECK(not producer2.pop().has_value());

  producer1.push(1138);

  CHECK(not consumer1.empty());
  CHECK(consumer1.size() == 1);
  CHECK(consumer1.running());

  CHECK(not producer1.empty());
  CHECK(consumer1.size() == 1);
  CHECK(producer1.running());

  CHECK(not consumer2.empty());
  CHECK(consumer2.size() == 1);
  CHECK(consumer2.running());

  CHECK(not producer2.empty());
  CHECK(consumer2.size() == 1);
  CHECK(producer2.running());

  CHECK(consumer1.pop().has_value());

  CHECK(not producer1.pop().has_value());
  CHECK(not consumer2.pop().has_value());
  CHECK(not producer2.pop().has_value());

  producer2.push(1138);

  CHECK(not consumer1.empty());
  CHECK(consumer1.size() == 1);
  CHECK(consumer1.running());

  CHECK(not producer1.empty());
  CHECK(consumer1.size() == 1);
  CHECK(producer1.running());

  CHECK(not consumer2.empty());
  CHECK(consumer2.size() == 1);
  CHECK(consumer2.running());

  CHECK(not producer2.empty());
  CHECK(consumer2.size() == 1);
  CHECK(producer2.running());

  CHECK(consumer1.pop().has_value());

  CHECK(not producer1.pop().has_value());
  CHECK(not consumer2.pop().has_value());
  CHECK(not producer2.pop().has_value());

  producer1.push(42);
  CHECK(*consumer1.pop() == 42);
}
