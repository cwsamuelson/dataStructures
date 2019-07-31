cmake_minimum_required(VERSION 3.0)
project(named_point LANGUAGES CXX)

if(TARGET named_point)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET named_type)
	add_subdirectory("../named_type/" named_type)
endif()
if(NOT TARGET array)
	add_subdirectory("../array/" array)
endif()

add_library(named_point INTERFACE)

set_target_properties(named_point PROPERTIES
                                  INTERFACE_CXX_STANDARD 17
                                  INTERFACE_CXX_STANDARD_REQUIRED YES
                                  INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(named_point INTERFACE .)
target_link_libraries(named_point INTERFACE named_type INTERFACE array)

add_executable(test-named_point tests.cc)
set_target_properties(test-named_point PROPERTIES
                                       CXX_STANDARD 17
                                       CXX_STANDARD_REQUIRED YES
                                       CXX_EXTENSIONS NO)
target_link_libraries(test-named_point named_point Catch2)

enable_testing()
add_test(test-named_point test-named_point)

