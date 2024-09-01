cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_core LANGUAGES CXX)

set(HEADERS
  header/core/additive.hh
  header/core/comparative.hh
  header/core/concepts.hh
  header/core/multiplicative.hh
  header/core/normal_iterator.hh
  header/core/operators.hh
  header/core/traits.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE
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

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

