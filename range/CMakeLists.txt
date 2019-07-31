cmake_minimum_required(VERSION 3.0)
project(range LANGUAGES CXX)

if(TARGET range)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(range INTERFACE)

set_target_properties(range PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(range INTERFACE .)

add_executable(test-range tests.cc)
set_target_properties(test-range PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-range range Catch2)

enable_testing()
add_test(test-range test-range)

