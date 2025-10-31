cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_random LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/core/random/distributions/normal.hh
  header/core/random/distributions/uniform.hh
  header/core/random/engines/linear-congruential.hh
  header/core/random/engines/mersenne-twister.hh
  header/core/random/engines/philox.hh
  header/core/random/engines/subtract-with-carry.hh
  header/core/random/sources/seed.hh
  header/core/random/random.hh
)
set(SOURCES
  source/seed.cc
)

common_library(${PROJECT_NAME}
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
  PUBLIC
  ${BASE_PROJECT}_core
  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)
