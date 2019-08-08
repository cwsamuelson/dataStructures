cmake_minimum_required(VERSION 3.0)
project(region_tree LANGUAGES CXX)

if(TARGET region_tree)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(region_tree INTERFACE)

set_target_properties(region_tree PROPERTIES
                                  INTERFACE_CXX_STANDARD 17
                                  INTERFACE_CXX_STANDARD_REQUIRED YES
                                  INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(region_tree INTERFACE .)

add_executable(test-region_tree tests.cc)
set_target_properties(test-region_tree PROPERTIES
                                       CXX_STANDARD 17
                                       CXX_STANDARD_REQUIRED YES
                                       CXX_EXTENSIONS NO)
target_link_libraries(test-region_tree region_tree Catch2)

enable_testing()
add_test(test-region_tree test-region_tree)

