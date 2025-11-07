cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_canvas LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/canvas/canvas.hh
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
  error_support::error_support

  ${BASE_PROJECT}_core
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

common_executable(${PROJECT_NAME}_exe
  source/main.cc
)

target_include_directories(${PROJECT_NAME}_exe
  PUBLIC
  source
)

target_link_libraries(${PROJECT_NAME}_exe
  PUBLIC
  ${PROJECT_NAME}
)
