cmake_minimum_required(VERSION 3.0)
project(logger LANGUAGES CXX)

if(TARGET logger)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(logger INTERFACE)

set_target_properties(logger PROPERTIES
                             INTERFACE_CXX_STANDARD 17
                             INTERFACE_CXX_STANDARD_REQUIRED YES
                             INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(logger INTERFACE header)

add_executable(test-logger test/tests.cc)
set_target_properties(test-logger PROPERTIES
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED YES
                                  CXX_EXTENSIONS NO)
target_link_libraries(test-logger logger Catch2)

enable_testing()
add_test(test-logger test-logger)

