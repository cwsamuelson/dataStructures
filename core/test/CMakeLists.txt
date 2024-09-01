set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)

common_test(${PROJECT_NAME}
  additive.cc
  comparative.cc
  concepts.cc
  multiplicative.cc
  normal_iterator.cc
  operators.cc
  #tests.cc# this is more a template..
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Catch2::Catch2WithMain
  ${BASE_PROJECT}
)

enable_testing()
include(Catch)
catch_discover_tests(${PROJECT_NAME})

