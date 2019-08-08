cmake_minimum_required(VERSION 3.0)
project(operators LANGUAGES CXX)

if(TARGET operators)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(operators INTERFACE)

set_target_properties(operators PROPERTIES
                                INTERFACE_CXX_STANDARD 17
                                INTERFACE_CXX_STANDARD_REQUIRED YES
                                INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(operators INTERFACE .)

add_executable(test-operators tests.cc)
set_target_properties(test-operators PROPERTIES
                                     CXX_STANDARD 17
                                     CXX_STANDARD_REQUIRED YES
                                     CXX_EXTENSIONS NO)
target_link_libraries(test-operators operators Catch2)

enable_testing()
add_test(test-operators test-operators)

