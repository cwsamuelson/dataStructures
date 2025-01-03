set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)

common_test(${PROJECT_NAME}
  tests.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Catch2::Catch2WithMain
  ${BASE_PROJECT}
)

include(Catch)
catch_discover_tests(${PROJECT_NAME})

