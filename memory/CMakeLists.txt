cmake_minimum_required(VERSION 3.0)
project(memory_pool LANGUAGES CXX)

if(TARGET memory_pool)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(memory_pool INTERFACE)

set_target_properties(memory_pool PROPERTIES
                                  INTERFACE_CXX_STANDARD 17
                                  INTERFACE_CXX_STANDARD_REQUIRED YES
                                  INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(memory_pool INTERFACE header)

add_executable(test-memory_pool test/tests.cc)
set_target_properties(test-memory_pool PROPERTIES
                                       CXX_STANDARD 17
                                       CXX_STANDARD_REQUIRED YES
                                       CXX_EXTENSIONS NO)
target_link_libraries(test-memory_pool memory_pool Catch2)

enable_testing()
add_test(test-memory_pool test-memory_pool)

