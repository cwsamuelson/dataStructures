cmake_minimum_required(VERSION 3.0)
project(ratio LANGUAGES CXX)

if(TARGET ratio)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(ratio INTERFACE)

set_target_properties(ratio PROPERTIES
                                    INTERFACE_CXX_STANDARD 17
                                    INTERFACE_CXX_STANDARD_REQUIRED YES
                                    INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(ratio INTERFACE .)

add_executable(test-ratio tests.cc)
set_target_properties(test-ratio PROPERTIES
                                         CXX_STANDARD 17
                                         CXX_STANDARD_REQUIRED YES
                                         CXX_EXTENSIONS NO)
target_link_libraries(test-ratio ratio Catch2)

enable_testing()
add_test(test-ratio test-ratio)

