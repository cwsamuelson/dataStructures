cmake_minimum_required(VERSION 3.0)
project(list LANGUAGES CXX)

if(TARGET list)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()

add_library(list INTERFACE)

set_target_properties(list PROPERTIES
                           INTERFACE_CXX_STANDARD 17
                           INTERFACE_CXX_STANDARD_REQUIRED YES
                           INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(list INTERFACE .)
target_link_libraries(list INTERFACE normal_iterator)

add_executable(test-list tests.cc)
set_target_properties(test-list PROPERTIES
                                CXX_STANDARD 17
                                CXX_STANDARD_REQUIRED YES
                                CXX_EXTENSIONS NO)
target_link_libraries(test-list list Catch2)

enable_testing()
add_test(test-list test-list)

