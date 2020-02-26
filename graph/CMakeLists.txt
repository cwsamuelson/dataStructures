cmake_minimum_required(VERSION 3.0)
project(graph LANGUAGES CXX)

if(TARGET graph)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(graph INTERFACE)

set_target_properties(graph PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)
target_include_directories(graph INTERFACE header)

add_executable(test-graph test/tests.cc)
set_target_properties(test-graph PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-graph graph Catch2)

enable_testing()
add_test(test-graph test-graph)

