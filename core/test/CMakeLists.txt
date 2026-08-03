set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)
find_package(rapidcheck REQUIRED)

common_test(${PROJECT_NAME}
  additive.cc
  any.cc
  applications.cc
  comparative.cc
  concepts.cc
  curryable.cc
  expected.cc
  function-traits.cc
  multiplicative.cc
  normal_iterator.cc
  number.cc
  operators.cc
  overloads.cc
  property.cc
  random.cc
  #ranges.cc
  red-black-tree.cc
  refs.cc
  span.cc
  tagged_type.cc
  traits.cc
  type-pack.cc
  variant.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Catch2::Catch2WithMain
  rapidcheck::rapidcheck

  ${BASE_PROJECT}
  ${BASE_PROJECT}::base
)

enable_testing()
include(Catch)
catch_discover_tests(${PROJECT_NAME})

