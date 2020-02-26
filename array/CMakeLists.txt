cmake_minimum_required(VERSION 3.0)
project(array LANGUAGES CXX)

if(TARGET array)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()

add_library(array INTERFACE)

set_target_properties(array PROPERTIES
                                    INTERFACE_CXX_STANDARD 17
                                    INTERFACE_CXX_STANDARD_REQUIRED YES
                                    INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(array INTERFACE header)
target_link_libraries(array INTERFACE normal_iterator)

add_executable(test-array test/tests.cc)
set_target_properties(test-array PROPERTIES
                                         CXX_STANDARD 17
                                         CXX_STANDARD_REQUIRED YES
                                         CXX_EXTENSIONS NO)
target_link_libraries(test-array array Catch2)

enable_testing()
add_test(test-array test-array)

