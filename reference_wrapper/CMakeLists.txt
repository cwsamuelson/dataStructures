cmake_minimum_required(VERSION 3.0)
project(reference_wrapper LANGUAGES CXX)

if(TARGET reference_wrapper)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(reference_wrapper INTERFACE)

set_target_properties(reference_wrapper PROPERTIES
                                        INTERFACE_CXX_STANDARD 17
                                        INTERFACE_CXX_STANDARD_REQUIRED YES
                                        INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(reference_wrapper INTERFACE header)
target_link_libraries(reference_wrapper INTERFACE tuple)

add_executable(test-reference_wrapper test/tests.cc)
set_target_properties(test-reference_wrapper PROPERTIES
                                             CXX_STANDARD 17
                                             CXX_STANDARD_REQUIRED YES
                                             CXX_EXTENSIONS NO)
target_link_libraries(test-reference_wrapper reference_wrapper Catch2)

enable_testing()
add_test(test-reference_wrapper test-reference_wrapper)

