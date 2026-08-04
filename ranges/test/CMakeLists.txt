set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)
find_package(rapidcheck REQUIRED)

common_test(${PROJECT_NAME}
  all.cc
  chunk-by.cc
  chunk.cc
  drop-while.cc
  drop.cc
  enumerate.cc
  filter.cc
  generate.cc
  iota.cc
  join.cc
  repeat.cc
  reverse.cc
  slide.cc
  split.cc
  take-while.cc
  take.cc
  transform.cc
  value.cc
  zip.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Catch2::Catch2WithMain
  rapidcheck::rapidcheck

  ${BASE_PROJECT}
)

enable_testing()
include(Catch)
catch_discover_tests(${PROJECT_NAME})
