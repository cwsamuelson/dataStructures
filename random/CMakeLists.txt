cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_random LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/core/random/distribution/normal.hh
  header/core/random/distribution/uniform.hh
  header/core/random/engine/branching.hh
  header/core/random/engine/linear-congruential.hh
  header/core/random/engine/mersenne-twister.hh
  header/core/random/engine/monotonic.hh
  header/core/random/engine/philox.hh
  header/core/random/engine/subtract-with-carry.hh
  header/core/random/source/dev-random.hh
  header/core/random/random.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME}
  INTERFACE
  ${HEADERS}
  ${SOURCES}
)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${BASE_PROJECT}_core
  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)
