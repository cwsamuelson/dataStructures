cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_core LANGUAGES CXX)

find_package(Boost REQUIRED)

set(HEADERS
  header/core/additive.hh
  header/core/aligned-buffer.hh
  header/core/any.hh
  header/core/application.hh
  header/core/comparative.hh
  header/core/concepts.hh
  header/core/curryable.hh
  header/core/dyn-mdspan.hh
  header/core/expected.hh
  header/core/forward-ref.hh
  header/core/hash-combine.hh
  header/core/layer.hh
  header/core/maybe_const.hh
  header/core/mdspan.hh
  header/core/move-ref.hh
  header/core/multiplicative.hh
  header/core/normal_iterator.hh
  header/core/number.hh
  header/core/operators.hh
  header/core/overloads.hh
  header/core/property.hh
  header/core/random/distribution
  header/core/random/distribution/bernoulli.hh
  header/core/random/distribution/bernoulli/bernoulli.hh
  header/core/random/distribution/bernoulli/binomial.hh
  header/core/random/distribution/bernoulli/geometric.hh
  header/core/random/distribution/bernoulli/negative-binomial.hh
  header/core/random/distribution/normal.hh
  header/core/random/distribution/normal/cauchy.hh
  header/core/random/distribution/normal/chi-squared.hh
  header/core/random/distribution/normal/fisher-f.hh
  header/core/random/distribution/normal/lognormal.hh
  header/core/random/distribution/normal/normal.hh
  header/core/random/distribution/normal/student-t.hh
  header/core/random/distribution/poisson.hh
  header/core/random/distribution/poisson/exponential.hh
  header/core/random/distribution/poisson/extreme-value.hh
  header/core/random/distribution/poisson/gamma.hh
  header/core/random/distribution/poisson/poisson.hh
  header/core/random/distribution/poisson/weibull.hh
  header/core/random/distribution/sampling.hh
  header/core/random/distribution/sampling/discrete.hh
  header/core/random/distribution/sampling/piecewise-constant.hh
  header/core/random/distribution/sampling/piecewise-linear.hh
  header/core/random/distribution/uniform.hh
  header/core/random/distribution/uniform/floating-point.hh
  header/core/random/distribution/uniform/integer.hh
  header/core/random/engine/branching.hh
  header/core/random/engine/linear-congruential.hh
  header/core/random/engine/mersenne-twister.hh
  header/core/random/engine/monotonic.hh
  header/core/random/engine/philox.hh
  header/core/random/engine/subtract-with-carry.hh
  header/core/random/random.hh
  header/core/random/source/dev-random.hh
  header/core/random/source/dev-urandom.hh
  header/core/random/tools/perlin-noise.hh
  header/core/range.hh
  header/core/rb-tree.hh
  header/core/span.hh
  header/core/tagged_type.hh
  header/core/traits.hh
  header/core/traits/const.hh
  header/core/traits/function.hh
  header/core/traits/impl/const.hh
  header/core/traits/impl/pointer.hh
  header/core/traits/impl/reference.hh
  header/core/traits/impl/volatile.hh
  header/core/traits/integral.hh
  header/core/traits/pointer.hh
  header/core/traits/reference.hh
  header/core/traits/value_types.hh
  header/core/traits/volatile.hh
  header/core/type-pack.hh
  header/core/variant.hh
  header/core/verify.hh
)
set(SOURCES
  source/application.cc
  source/layer.cc
)

common_library(${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${BASE_PROJECT}_algorithms

  Boost::boost
)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${HEADERS}
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

add_library(${PROJECT_NAME}::base ALIAS ${PROJECT_NAME})

####

set(WRAP_HEADERS
  header/core/main.hh
)
set(WRAP_SOURCES
  source/main-wrap.cc
)

add_library(${PROJECT_NAME}_main_wrap
  ${WRAP_HEADERS}
  ${WRAP_SOURCES}
)

target_sources(${PROJECT_NAME}_main_wrap
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${WRAP_HEADERS}
)

target_link_libraries(${PROJECT_NAME}_main_wrap
  PUBLIC
  ${PROJECT_NAME}::base
)

install(TARGETS ${PROJECT_NAME}_main_wrap FILE_SET public_headers)

add_library(${PROJECT_NAME}::main_wrap ALIAS ${PROJECT_NAME}_main_wrap)

####

set(MAIN_HEADERS
)
set(MAIN_SOURCES
  source/main.cc
)

add_library(${PROJECT_NAME}_main
  ${MAIN_HEADERS}
  ${MAIN_SOURCES}
)

target_sources(${PROJECT_NAME}_main
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${MAIN_HEADERS}
)

target_link_libraries(${PROJECT_NAME}_main
  PUBLIC
  ${PROJECT_NAME}::main_wrap
)

install(TARGETS ${PROJECT_NAME}_main FILE_SET public_headers)

add_library(${PROJECT_NAME}::main ALIAS ${PROJECT_NAME}_main)
