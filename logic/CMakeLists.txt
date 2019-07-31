cmake_minimum_required(VERSION 3.0)
project(logic LANGUAGES CXX)

if(TARGET logic)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(logic logic.cc)

set_target_properties(logic PROPERTIES
                            CXX_STANDARD 17
                            CXX_STANDARD_REQUIRED YES
                            CXX_EXTENSIONS NO)

target_include_directories(logic PUBLIC .)

add_executable(test-logic tests.cc)
set_target_properties(test-logic PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-logic logic Catch2)

enable_testing()
add_test(test-logic test-logic)

