cmake_minimum_required(VERSION 3.0)
project(function LANGUAGES CXX)

if(TARGET function)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(function INTERFACE)

set_target_properties(function PROPERTIES
                               INTERFACE_CXX_STANDARD 17
                               INTERFACE_CXX_STANDARD_REQUIRED YES
                               INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(function INTERFACE .)
target_link_libraries(function INTERFACE tuple)

add_executable(test-function tests.cc)
set_target_properties(test-function PROPERTIES
                                    CXX_STANDARD 17
                                    CXX_STANDARD_REQUIRED YES
                                    CXX_EXTENSIONS NO)
target_link_libraries(test-function function Catch2)

enable_testing()
add_test(test-function test-function)

