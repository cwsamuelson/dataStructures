cmake_minimum_required(VERSION 3.0)
project(trie LANGUAGES CXX)

if(TARGET trie)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(trie INTERFACE)

set_target_properties(trie PROPERTIES
                           INTERFACE_CXX_STANDARD 17
                           INTERFACE_CXX_STANDARD_REQUIRED YES
                           INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(trie INTERFACE .)
target_link_libraries(trie INTERFACE tuple)

add_executable(test-trie tests.cc)
set_target_properties(test-trie PROPERTIES
                                CXX_STANDARD 17
                                CXX_STANDARD_REQUIRED YES
                                CXX_EXTENSIONS NO)
target_link_libraries(test-trie trie Catch2)

enable_testing()
add_test(test-trie test-trie)

