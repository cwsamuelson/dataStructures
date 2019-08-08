cmake_minimum_required(VERSION 3.0)
project(lambda LANGUAGES CXX)

if(TARGET lambda)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(lambda INTERFACE)

set_target_properties(lambda PROPERTIES
                             INTERFACE_CXX_STANDARD 17
                             INTERFACE_CXX_STANDARD_REQUIRED YES
                             INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(lambda INTERFACE .)

add_executable(test-lambda tests.cc)
set_target_properties(test-lambda PROPERTIES
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED YES
                                  CXX_EXTENSIONS NO)
target_link_libraries(test-lambda lambda Catch2)

enable_testing()
add_test(test-lambda test-lambda)

