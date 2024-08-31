cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(operators LANGUAGES CXX)

set(HEADERS
  header/additive.hh
  header/comparitive.hh
  header/multiplicative.hh
  header/operators.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
  INTERFACE
  header
)

enable_testing()
add_subdirectory(test)

