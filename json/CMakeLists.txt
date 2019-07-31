cmake_minimum_required(VERSION 3.0)
project(json LANGUAGES CXX)

if(TARGET json)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(json INTERFACE)

set_target_properties(json PROPERTIES
                           INTERFACE_CXX_STANDARD 17
                           INTERFACE_CXX_STANDARD_REQUIRED YES
                           INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(json INTERFACE .)
#target_link_libraries(json INTERFACE tuple)

add_executable(test-json tests.cc)
set_target_properties(test-json PROPERTIES
                                CXX_STANDARD 17
                                CXX_STANDARD_REQUIRED YES
                                CXX_EXTENSIONS NO)
target_link_libraries(test-json json Catch2)

enable_testing()
add_test(test-json test-json)

