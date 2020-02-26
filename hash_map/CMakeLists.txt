cmake_minimum_required(VERSION 3.0)
project(hash_map LANGUAGES CXX)

if(TARGET hash_map)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET normal_iterator)
	add_subdirectory("../normal_iterator/" normal_iterator)
endif()
if(NOT TARGET allocator)
	add_subdirectory("../allocator/" allocator)
endif()

add_library(hash_map INTERFACE)

set_target_properties(hash_map PROPERTIES
                               INTERFACE_CXX_STANDARD 17
                               INTERFACE_CXX_STANDARD_REQUIRED YES
                               INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(hash_map INTERFACE header)
target_link_libraries(hash_map INTERFACE normal_iterator
                               INTERFACE allocator)

add_executable(test-hash_map test/tests.cc)
set_target_properties(test-hash_map PROPERTIES
                                    CXX_STANDARD 17
                                    CXX_STANDARD_REQUIRED YES
                                    CXX_EXTENSIONS NO)
target_link_libraries(test-hash_map hash_map Catch2)

enable_testing()
add_test(test-hash_map test-hash_map)

