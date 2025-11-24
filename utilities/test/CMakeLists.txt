set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

configure_file(input_file.txt input_file.txt COPYONLY)

find_package(Catch2 REQUIRED)
find_package(rapidcheck REQUIRED)

common_test(${PROJECT_NAME}
  tests.cc
  base64.cc
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
