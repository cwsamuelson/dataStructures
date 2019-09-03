cmake_minimum_required(VERSION 3.0)
project(threadPool LANGUAGES CXX)

if(TARGET threadPool)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(threadPool INTERFACE)

set_target_properties(threadPool PROPERTIES
                                    INTERFACE_CXX_STANDARD 17
                                    INTERFACE_CXX_STANDARD_REQUIRED YES
                                    INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(threadPool INTERFACE .)
#target_link_libraries(threadPool INTERFACE tuple)

add_executable(test-threadPool tests.cc)
set_target_properties(test-threadPool PROPERTIES
                                         CXX_STANDARD 17
                                         CXX_STANDARD_REQUIRED YES
                                         CXX_EXTENSIONS NO)
target_link_libraries(test-threadPool threadPool Catch2)

enable_testing()
add_test(test-threadPool test-threadPool)

