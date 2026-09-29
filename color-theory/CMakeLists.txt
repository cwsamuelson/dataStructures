cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_color-theory LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/color_theory/color_theory.hh
  header/color_theory/convert.hh
  header/color_theory/cmyk/cmyk.hh
  header/color_theory/hsl/hsl.hh
  header/color_theory/hsv/hsv.hh
  header/color_theory/lab/lab.hh
  header/color_theory/linear_rgb/linear_rgb.hh
  header/color_theory/srgb/srgb.hh
  header/color_theory/xyz/xyz.hh
  header/color_theory/conversions/hsx_common.hh
  header/color_theory/conversions/linear_rgb_xyz.hh
  header/color_theory/conversions/srgb_cmyk.hh
  header/color_theory/conversions/srgb_hsl.hh
  header/color_theory/conversions/srgb_hsv.hh
  header/color_theory/conversions/srgb_linear_rgb.hh
  header/color_theory/conversions/xyz_lab.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE
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
  INTERFACE
  ${BASE_PROJECT}_core
  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)
