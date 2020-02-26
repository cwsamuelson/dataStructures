cmake_minimum_required(VERSION 3.0)
project(skip_list LANGUAGES CXX)

if(TARGET skip_list)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../tuple/" normal_iterator)
endif()

add_library(skip_list INTERFACE)

set_target_properties(skip_list PROPERTIES
                                INTERFACE_CXX_STANDARD 17
                                INTERFACE_CXX_STANDARD_REQUIRED YES
                                INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(skip_list INTERFACE header)
target_link_libraries(skip_list INTERFACE normal_iterator)

add_executable(test-skip_list test/tests.cc)
set_target_properties(test-skip_list PROPERTIES
                                     CXX_STANDARD 17
                                     CXX_STANDARD_REQUIRED YES
                                     CXX_EXTENSIONS NO)
target_link_libraries(test-skip_list skip_list Catch2)

enable_testing()
add_test(test-skip_list test-skip_list)

