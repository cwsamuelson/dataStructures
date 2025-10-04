cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_ranges LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/ranges/all.hh
  header/ranges/chunk-by.hh
  header/ranges/chunk.hh
  header/ranges/drop-while.hh
  header/ranges/drop.hh
  header/ranges/enumerate.hh
  header/ranges/filter.hh
  header/ranges/generate.hh
  header/ranges/iota.hh
  header/ranges/join.hh
  header/ranges/repeating.hh
  header/ranges/reverse.hh
  header/ranges/slide.hh
  header/ranges/split.hh
  header/ranges/take-while.hh
  header/ranges/take.hh
  header/ranges/traits.hh
  header/ranges/transform.hh
  header/ranges/value.hh
  header/ranges/zip.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE
  ${HEADERS}
  ${SOURCES}
)

target_compile_options(${PROJECT_NAME}
  INTERFACE
  -fconcepts-diagnostics-depth=8
)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  #${BASE_PROJECT}_core
  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

