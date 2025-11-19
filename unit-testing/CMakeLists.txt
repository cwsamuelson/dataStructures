cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_unit-testing LANGUAGES CXX)

find_package(error_support REQUIRED)
find_package(lyra REQUIRED)
find_package(nlohmann_json REQUIRED)

set(HEADERS
  header/testing/framework.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  bfg::lyra
  nlohmann_json::nlohmann_json

  error_support::error_support

  ${BASE_PROJECT}_core
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)
