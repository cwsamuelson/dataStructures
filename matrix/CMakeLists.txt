cmake_minimum_required(VERSION 3.0)
project(matrix LANGUAGES CXX)

if(TARGET matrix)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET operators)
	add_subdirectory("../operators/" operators)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()

add_library(matrix INTERFACE)

set_target_properties(matrix PROPERTIES
                             INTERFACE_CXX_STANDARD 17
                             INTERFACE_CXX_STANDARD_REQUIRED YES
                             INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(matrix INTERFACE header)
target_link_libraries(matrix INTERFACE tuple)

add_executable(test-matrix test/tests.cc)
set_target_properties(test-matrix PROPERTIES
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED YES
                                  CXX_EXTENSIONS NO)
target_link_libraries(test-matrix matrix Catch2)

enable_testing()
add_test(test-matrix test-matrix)

