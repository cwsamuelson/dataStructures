cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_shape LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/shapes/functions.hh
  header/shapes/mat2.hh
  header/shapes/mat3.hh
  header/shapes/mat4.hh
  header/shapes/shapes.hh
  header/shapes/swizzle_macros.hh
  header/shapes/swizzling.hh
  header/shapes/vec2.hh
  header/shapes/vec3.hh
  header/shapes/vec4.hh
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
  ${BASE_PROJECT}_core
  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)
