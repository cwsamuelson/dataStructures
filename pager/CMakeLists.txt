cmake_minimum_required(VERSION 3.0)
project(pager LANGUAGES CXX)

if(TARGET pager)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()

add_library(pager pager.cc pager.hh)

set_target_properties(pager PROPERTIES
                            INTERFACE_CXX_STANDARD 17
                            INTERFACE_CXX_STANDARD_REQUIRED YES
                            INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(pager PUBLIC .)
target_link_libraries(pager PRIVATE polynomial)

add_executable(test-pager tests.cc)
set_target_properties(test-pager PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)
target_link_libraries(test-pager pager Catch2)

enable_testing()
add_test(test-pager test-pager)

