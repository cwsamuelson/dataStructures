cmake_minimum_required(VERSION 3.0)
project(normal_iterator LANGUAGES CXX)

if(TARGET normal_iterator)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET operators)
	add_subdirectory("../operators/" operators)
endif()

add_library(normal_iterator INTERFACE)

set_target_properties(normal_iterator PROPERTIES
                                      INTERFACE_CXX_STANDARD 17
                                      INTERFACE_CXX_STANDARD_REQUIRED YES
                                      INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(normal_iterator INTERFACE header)

target_link_libraries(normal_iterator INTERFACE operators)

enable_testing()

add_executable(test-normal_iterator test/tests.cc)
set_target_properties(test-normal_iterator PROPERTIES
                                           CXX_STANDARD 17
                                           CXX_STANDARD_REQUIRED YES
                                           CXX_EXTENSIONS NO)
target_link_libraries(test-normal_iterator normal_iterator Catch2)
add_test(test-normal_iterator test-normal_iterator)

