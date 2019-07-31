cmake_minimum_required(VERSION 3.0)
project(menu LANGUAGES CXX)

if(TARGET menu)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(menu INTERFACE)

set_target_properties(menu PROPERTIES
                           INTERFACE_CXX_STANDARD 17
                           INTERFACE_CXX_STANDARD_REQUIRED YES
                           INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(menu INTERFACE .)

add_executable(test-menu tests.cc)
set_target_properties(test-menu PROPERTIES
                                CXX_STANDARD 17
                                CXX_STANDARD_REQUIRED YES
                                CXX_EXTENSIONS NO)
target_link_libraries(test-menu menu Catch2)

enable_testing()
add_test(test-menu test-menu)

