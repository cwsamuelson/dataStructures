cmake_minimum_required(VERSION 3.0)
project(string LANGUAGES CXX)

if(TARGET string)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET allocator)
	add_subdirectory("../allocator/" allocator)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()

add_library(string INTERFACE)

set_target_properties(string PROPERTIES
                             INTERFACE_CXX_STANDARD 17
                             INTERFACE_CXX_STANDARD_REQUIRED YES
                             INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(string INTERFACE .)
target_link_libraries(string INTERFACE tuple
                             INTERFACE allocator
                             INTERFACE normal_iterator)

add_executable(test-string tests.cc)
set_target_properties(test-string PROPERTIES
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED YES
                                  CXX_EXTENSIONS NO)
target_link_libraries(test-string string Catch2)

enable_testing()
add_test(test-string test-string)

