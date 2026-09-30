set(BASE_PROJECT ${PROJECT_NAME})
project(${PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(rapidcheck REQUIRED)

common_test(${PROJECT_NAME}
  tests.cc
)

configure_file(test.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Catch2::Catch2WithMain
  rapidcheck::rapidcheck
  nlohmann_json::nlohmann_json

  ${BASE_PROJECT}
)

enable_testing()
include(Catch)
catch_discover_tests(${PROJECT_NAME})
