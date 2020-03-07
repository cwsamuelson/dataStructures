cmake_minimum_required(VERSION 3.0)
project(error LANGUAGES CXX)

if(TARGET error)
    return()
endif()

if(NOT TARGET Catch2)
    add_subdirectory("../catch/" Catch2)
endif()

add_library(error INTERFACE)

set_target_properties(error PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(error INTERFACE header)
target_link_libraries(error INTERFACE tuple)

add_executable(test-error test/tests.cc)
set_target_properties(test-error PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-error error Catch2)

enable_testing()
add_test(test-error test-error)

