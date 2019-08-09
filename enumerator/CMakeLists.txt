cmake_minimum_required(VERSION 3.0)
project(enumerator LANGUAGES CXX)

if(TARGET enumerator)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(enumerator INTERFACE)

set_target_properties(enumerator PROPERTIES
                                 INTERFACE_CXX_STANDARD 17
                                 INTERFACE_CXX_STANDARD_REQUIRED YES
                                 INTERFACE_CXX_EXTENSIONS NO)
target_include_directories(enumerator INTERFACE .)

add_executable(test-enumerator tests.cc)
set_target_properties(test-enumerator PROPERTIES
                                      CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED YES
                                      CXX_EXTENSIONS NO)
target_link_libraries(test-enumerator enumerator Catch2)

enable_testing()
add_test(test-enumerator test-enumerator)

