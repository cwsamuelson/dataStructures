cmake_minimum_required(VERSION 3.0)
project(traits LANGUAGES CXX)

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(traits INTERFACE)

set_target_properties(traits PROPERTIES
                               INTERFACE_CXX_STANDARD 17
                               INTERFACE_CXX_STANDARD_REQUIRED YES
                               INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(traits INTERFACE header)

add_executable(test-traits test/tests.cc)
set_target_properties(test-traits PROPERTIES
                              CXX_STANDARD 17
                              CXX_STANDARD_REQUIRED YES
                              CXX_EXTENSIONS NO)
target_link_libraries(test-traits traits Catch2)

enable_testing()
add_test(test-traits test-traits)

