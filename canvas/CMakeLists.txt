cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_canvas LANGUAGES CXX)

find_package(error_support REQUIRED)

# All font header files are based on files found in
# `https://github.com/dhepper/font8x8`.  They have been taken and adapted for
# C++.
set(HEADERS
  header/canvas/canvas.hh
  header/fonts/8x8.hh
  header/fonts/8x8_basic.hh
  header/fonts/8x8_block.hh
  header/fonts/8x8_box.hh
  header/fonts/8x8_control.hh
  header/fonts/8x8_ext_latin.hh
  header/fonts/8x8_greek.hh
  header/fonts/8x8_hiragana.hh
  header/fonts/8x8_latin.hh
  header/fonts/8x8_misc.hh
  header/fonts/8x8_sga.hh
  header/utility/graphical-term.hh
  header/ui/button.hh
  header/ui/control.hh
  header/ui/manager.hh
  header/ui/style.hh
  header/ui/widget.hh
)
set(SOURCES
  source/button.cc
  source/check-box.cc
  source/manager.cc
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
