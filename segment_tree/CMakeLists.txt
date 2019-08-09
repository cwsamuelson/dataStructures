cmake_minimum_required(VERSION 3.0)
project(segment_tree LANGUAGES CXX)

if(TARGET segment_tree)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(segment_tree INTERFACE)

set_target_properties(segment_tree PROPERTIES
                                    INTERFACE_CXX_STANDARD 17
                                    INTERFACE_CXX_STANDARD_REQUIRED YES
                                    INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(segment_tree INTERFACE .)

add_executable(test-segment_tree tests.cc)
set_target_properties(test-segment_tree PROPERTIES
                                        CXX_STANDARD 17
                                        CXX_STANDARD_REQUIRED YES
                                        CXX_EXTENSIONS NO)
target_link_libraries(test-segment_tree segment_tree Catch2)

enable_testing()
add_test(test-segment_tree test-segment_tree)

