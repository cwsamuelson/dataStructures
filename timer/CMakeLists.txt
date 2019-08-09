cmake_minimum_required(VERSION 3.0)
project(timer LANGUAGES CXX)

if(TARGET timer)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(timer INTERFACE)

set_target_properties(timer PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(timer INTERFACE .)

add_executable(test-timer tests.cc)
set_target_properties(test-timer PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-timer timer Catch2)

enable_testing()
add_test(test-timer test-timer)

