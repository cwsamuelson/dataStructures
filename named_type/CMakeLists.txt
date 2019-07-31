cmake_minimum_required(VERSION 3.0)
project(named_type LANGUAGES CXX)

if(TARGET named_type)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(named_type INTERFACE)

set_target_properties(named_type PROPERTIES
                                 INTERFACE_CXX_STANDARD 17
                                 INTERFACE_CXX_STANDARD_REQUIRED YES
                                 INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(named_type INTERFACE .)
target_link_libraries(named_type INTERFACE tuple)

add_executable(test-named_type tests.cc)
set_target_properties(test-named_type PROPERTIES
                                      CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED YES
                                      CXX_EXTENSIONS NO)
target_link_libraries(test-named_type named_type Catch2)

enable_testing()
add_test(test-named_type test-named_type)

