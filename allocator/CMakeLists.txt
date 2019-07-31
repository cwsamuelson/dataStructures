cmake_minimum_required(VERSION 3.0)
project(allocator LANGUAGES CXX)

if(TARGET allocator)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET algorithm)
	add_subdirectory("../algorithm/" algorithm)
endif()

add_library(allocator INTERFACE)

set_target_properties(allocator PROPERTIES
                                INTERFACE_CXX_STANDARD 17
                                INTERFACE_CXX_STANDARD_REQUIRED YES
                                INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(allocator INTERFACE .)

add_executable(test-allocator tests.cc)
set_target_properties(test-allocator PROPERTIES
                                     CXX_STANDARD 17
                                     CXX_STANDARD_REQUIRED YES
                                     CXX_EXTENSIONS NO)
target_link_libraries(test-allocator allocator Catch2 algorithms)

enable_testing()
add_test(test-allocator test-allocator)

