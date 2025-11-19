set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)

common_test(${PROJECT_NAME}
  tests.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${BASE_PROJECT}Main
)

enable_testing()
include(../cmake/test-discovery.cmake)
discover_tests(${PROJECT_NAME})
