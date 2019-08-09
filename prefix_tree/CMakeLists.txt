cmake_minimum_required(VERSION 3.0)
project(prefix_tree LANGUAGES CXX)

if(TARGET prefix_tree)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(prefix_tree INTERFACE)

set_target_properties(prefix_tree PROPERTIES
		                          INTERFACE_CXX_STANDARD 17
                                  INTERFACE_CXX_STANDARD_REQUIRED YES
                                  INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(prefix_tree INTERFACE .)
target_link_libraries(prefix_tree INTERFACE tuple)

add_executable(test-prefix_tree tests.cc)
set_target_properties(test-prefix_tree PROPERTIES
                                       CXX_STANDARD 17
                                       CXX_STANDARD_REQUIRED YES
                                       CXX_EXTENSIONS NO)
target_link_libraries(test-prefix_tree prefix_tree Catch2)

enable_testing()
add_test(test-prefix_tree test-prefix_tree)

