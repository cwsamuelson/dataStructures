cmake_minimum_required(VERSION 3.0)
project(remote LANGUAGES CXX)

if(TARGET remote)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(remote INTERFACE)

set_target_properties(remote PROPERTIES
                             INTERFACE_CXX_STANDARD 17
                             INTERFACE_CXX_STANDARD_REQUIRED YES
                             INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(remote INTERFACE .)
#target_link_libraries(remote INTERFACE tuple)

add_executable(test-remote tests.cc)
set_target_properties(test-remote PROPERTIES
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED YES
                                  CXX_EXTENSIONS NO)
target_link_libraries(test-remote remote Catch2)

enable_testing()
add_test(test-remote test-remote)

