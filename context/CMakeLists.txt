cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_context LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/context.hh
  header/containers.hh
  header/containers/deque.hh
  header/containers/forward_list.hh
  header/containers/list.hh
  header/containers/map.hh
  header/containers/set.hh
  header/containers/string.hh
  header/containers/unordered_map.hh
  header/containers/unordered_set.hh
  header/containers/vector.hh
  header/frame.hh
  header/traits.hh
  header/traits/allocator.hh
  header/traits/logger.hh
)
set(SOURCES
  source/context.cc
  source/base.cc
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

  ${BASE_PROJECT}_box
  ${BASE_PROJECT}_core
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)
