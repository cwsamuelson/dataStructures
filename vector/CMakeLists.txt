cmake_minimum_required(VERSION 3.0)
project(vector LANGUAGES CXX)

if(TARGET vector)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET vector)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()
if(NOT TARGET allocator)
	add_subdirectory("../allocator/" allocator)
endif()

add_library(vector INTERFACE)

set_target_properties(vector PROPERTIES
                              INTERFACE_CXX_STANDARD 17
                              INTERFACE_CXX_STANDARD_REQUIRED YES
                              INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(vector INTERFACE header)

target_link_libraries(vector INTERFACE normal_iterator allocator)

add_executable(test-vector test/tests.cc)
set_target_properties(test-vector PROPERTIES
                              CXX_STANDARD 17
                              CXX_STANDARD_REQUIRED YES
                              CXX_EXTENSIONS NO)
target_link_libraries(test-vector vector Catch2)

enable_testing()
add_test(test-vector test-vector)

