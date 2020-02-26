cmake_minimum_required(VERSION 3.0)
project(locked_resource LANGUAGES CXX)

if(TARGET locked_resource)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(locked_resource INTERFACE)

set_target_properties(locked_resource PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(locked_resource INTERFACE header)

add_executable(test-locked_resource test/tests.cc)
set_target_properties(test-locked_resource PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-locked_resource locked_resource Catch2)

enable_testing()
add_test(test-locked_resource test-locked_resource)

