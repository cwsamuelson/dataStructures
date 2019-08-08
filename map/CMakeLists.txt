cmake_minimum_required(VERSION 3.0)
project(map LANGUAGES CXX)

if(TARGET map)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()
if(NOT TARGET vector)
	add_subdirectory("../vector/" vector)
endif()
if(NOT TARGET tuple)
	add_subdirectory("../tuple/" tuple)
endif()
if(NOT TARGET allocator)
	add_subdirectory("../allocator/" allocator)
endif()

add_library(map INTERFACE)

set_target_properties(map PROPERTIES
                          INTERFACE_CXX_STANDARD 17
                          INTERFACE_CXX_STANDARD_REQUIRED YES
                          INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(map INTERFACE .)
target_link_libraries(map INTERFACE normal_iterator
                          INTERFACE vector
                          INTERFACE tuple
                          INTERFACE allocator)

add_executable(test-map tests.cc)
set_target_properties(test-map PROPERTIES
                               CXX_STANDARD 17
                               CXX_STANDARD_REQUIRED YES
                               CXX_EXTENSIONS NO)
target_link_libraries(test-map map Catch2)

enable_testing()
add_test(test-map test-map)

