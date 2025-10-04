set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)

common_test(${PROJECT_NAME}
  all_tests.cc
  # chunk-by_tests.cc
  # chunk_tests.cc
  # drop-while_tests.cc
  # enumerate_tests.cc
  filter_tests.cc
  generate_tests.cc
  iota_tests.cc
  # join_tests.cc
  # repeating_tests.cc
  # reverse_tests.cc
  # slide_tests.cc
  # split_tests.cc
  # take-while_tsets.cc
  take_tests.cc
  transform_tests.cc
  # value_tests.cc
  # zip_tests.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Catch2::Catch2WithMain
  ${BASE_PROJECT}
)

enable_testing()
include(Catch)
catch_discover_tests(${PROJECT_NAME})
