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
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE
  ${HEADERS}
  ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
  INTERFACE
  header
)

enable_testing()
add_subdirectory(test)

