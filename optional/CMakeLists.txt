cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_optional LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/optional.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${BASE_PROJECT}_core

  error_support::error_support
)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${HEADERS}
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

