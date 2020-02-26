cmake_minimum_required(VERSION 3.0)
project(unit LANGUAGES CXX)

if(TARGET unit)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET operators)
	add_subdirectory("../operators/" operators)
endif()
if(NOT TARGET ratio)
	add_subdirectory("../ratio/" ratio)
endif()

add_library(unit INTERFACE)

set_target_properties(unit PROPERTIES
                                    INTERFACE_CXX_STANDARD 17
                                    INTERFACE_CXX_STANDARD_REQUIRED YES
                                    INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(unit INTERFACE header)
target_link_libraries(unit INTERFACE operators INTERFACE ratio)

add_executable(test-unit test/tests.cc)
set_target_properties(test-unit PROPERTIES
                                         CXX_STANDARD 17
                                         CXX_STANDARD_REQUIRED YES
                                         CXX_EXTENSIONS NO)
target_link_libraries(test-unit unit Catch2)

enable_testing()
add_test(test-unit test-unit)

