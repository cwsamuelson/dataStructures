cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_versioning LANGUAGES CXX)

add_custom_target(${PROJECT_NAME}_generate
  ${CMAKE_COMMAND}
  -D HDR=${CMAKE_CURRENT_LIST_DIR}/version.hh.in
  -D SRC=${CMAKE_CURRENT_LIST_DIR}/version.cc.in
  -D HDST=${CMAKE_BINARY_DIR}/versioning/header/versioning/version.hh
  -D SDST=${CMAKE_BINARY_DIR}/versioning/source/version.cc
  -D VERSION_MAJOR=${${BASE_PROJECT}_VERSION_MAJOR}
  -D VERSION_MINOR=${${BASE_PROJECT}_VERSION_MINOR}
  -D VERSION_PATCH=${${BASE_PROJECT}_VERSION_PATCH}
  -D CI_BUILD_ID=${CI_BUILD_ID}
  -P ${CMAKE_CURRENT_LIST_DIR}/version.cmake
  BYPRODUCTS ${CMAKE_BINARY_DIR}/versioning/header/versioning/version.hh
  BYPRODUCTS ${CMAKE_BINARY_DIR}/versioning/source/version.cc
)

common_library(${PROJECT_NAME}
  ${CMAKE_BINARY_DIR}/versioning/header/versioning/version.hh
  ${CMAKE_BINARY_DIR}/versioning/source/version.cc
)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_generate)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_BINARY_DIR}/versioning/header
)

# this is a simpler implementation, but doesn't meet some basic needs
# using add_custom_target forces it to be run for every build, which ensures version information is always synchronized with git state
# keep version values in a source file to reduce cascading rebuilds
#add_custom_command(
#  OUTPUT ${CMAKE_BINARY_DIR}/versioning/header/version.hh
#  DEPENDS ${CMAKE_CURRENT_LIST_DIR}/version.hh.in
#  DEPENDS ${CMAKE_CURRENT_LIST_DIR}/version.cmake
#  COMMAND
#  ${CMAKE_COMMAND}
#  -D SRC=${CMAKE_CURRENT_LIST_DIR}/version.hh.in
#  -D DST=${CMAKE_BINARY_DIR}/versioning/header/version.hh
#  -P ${CMAKE_CURRENT_LIST_DIR}/version.cmake
#)

