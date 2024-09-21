#include <aligned_buffer.hh>
#include <core/additive.hh>
#include <core/comparative.hh>
#include <core/concepts.hh>
#include <core/multiplicative.hh>
#include <core/operators.hh>
#include <core/normal_iterator.hh>
#include <future.hh>
#include <optional.hh>
#include <producer_consumer.hpp>
#include <vector.hh>

int main(){
  flp::Vector<int> vector;
  flp::AlignedTypeBuffer<int> aligned_buffer;
  flp::Optional<int> optional;
  flp::Promise<int> promise;
  flp::Future<int> future = promise.get_future();
  const auto [producer, consumer] = flp::create_spsc<int>();
}
