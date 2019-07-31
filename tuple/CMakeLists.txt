cmake_minimum_required(VERSION 3.0)
project(tuple LANGUAGES CXX)

if(TARGET tuple)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(tuple INTERFACE)

set_target_properties(tuple PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(tuple INTERFACE .)

add_executable(test-tuple tests.cc)
set_target_properties(test-tuple PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-tuple tuple Catch2)

enable_testing()
add_test(test-tuple test-tuple)

