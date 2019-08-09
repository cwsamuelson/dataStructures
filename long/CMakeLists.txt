cmake_minimum_required(VERSION 3.0)
project(long LANGUAGES CXX)

if(TARGET long)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(long INTERFACE)

set_target_properties(long PROPERTIES
                           INTERFACE_CXX_STANDARD 17
                           INTERFACE_CXX_STANDARD_REQUIRED YES
                           INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(long INTERFACE .)

add_executable(test-long tests.cc)
set_target_properties(test-long PROPERTIES
                                CXX_STANDARD 17
                                CXX_STANDARD_REQUIRED YES
                                CXX_EXTENSIONS NO)
target_link_libraries(test-long long Catch2)

enable_testing()
add_test(test-long test-long)

