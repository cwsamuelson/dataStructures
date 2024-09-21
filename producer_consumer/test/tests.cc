#include <producer_consumer.hpp>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Producer consumer tests") {
    //std::cout << std::boolalpha;

    auto [producer, consumer] = create_spsc<int, SimpleStore_st<int>>();
    //std::cout << consumer.pop().has_value() << '\n';
    producer.push(1138);
    //std::cout << consumer.pop().has_value() << '\n';
    //std::cout << consumer.pop().has_value() << '\n';
    producer.push(42);
    [[maybe_unused]]auto value = *consumer.pop();
    //std::cout << value << '\n';
}

