#pragma once

#include "shape/vecn.hh"

namespace flp {

template<typename Type, size_t Count>
struct NormalizedVecN : vecn<Type, Count> {
  using base_vecn = vecn<Type, Count>;

  NormalizedVecN(const base_vecn& base)
    : base_vecn(base) {
    normalize(*this);
  }

  NormalizedVecN(const NormalizedVecn&) = default;
  NormalizedVecN(NormalizedVecn&&) noexcept = default;
  NormalizedVecN& operator=(const NormalizedVecn&) = default;
  NormalizedVecN& operator=(NormalizedVecn&&) noexcept = default;

  NormalizedVecN& operator=(const base_vecn& base) {
    return *this = NormalizedVecN(base);
  }
};

}
