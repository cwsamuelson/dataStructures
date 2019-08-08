cmake_minimum_required(VERSION 3.0)
project(accessor LANGUAGES CXX)

if(TARGET accessor)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(accessor INTERFACE)

set_target_properties(accessor PROPERTIES
                               INTERFACE_CXX_STANDARD 17
                               INTERFACE_CXX_STANDARD_REQUIRED YES
                               INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(accessor INTERFACE .)
target_link_libraries(accessor INTERFACE tuple)

add_executable(test-accessor tests.cc)
set_target_properties(test-accessor PROPERTIES
                                    CXX_STANDARD 17
                                    CXX_STANDARD_REQUIRED YES
                                    CXX_EXTENSIONS NO)
target_link_libraries(test-accessor accessor Catch2)

enable_testing()
add_test(test-accessor test-accessor)

