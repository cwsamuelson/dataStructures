#include "core/random/sources/seed.hh"

#include <chrono>

namespace flp::Random {

// namespace {
// 
// size_t rand(const size_t seed) {
//   return 0;
// }
// 
// size_t bounded_rand(size_t range) {
//   for (;;) {
//     const size_t x = rand();
//     const size_t r = x % range;;
// 
//     if (x - r <= -range) {
//       return r;
//     }
//   }
// }
// 
// }

Seed::Seed()
  : Seed(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{}

double Seed::entropy() const noexcept {
  return 0.;
}

}
