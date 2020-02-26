cmake_minimum_required(VERSION 3.0)
project(date_time LANGUAGES CXX)

if(TARGET date_time)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET unit)
	add_subdirectory("../unit/" unit)
endif()

add_library(date_time INTERFACE)

set_target_properties(date_time PROPERTIES
                                INTERFACE_CXX_STANDARD 17
                                INTERFACE_CXX_STANDARD_REQUIRED YES
                                INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(date_time INTERFACE header)
target_link_libraries(date_time INTERFACE unit)

add_executable(test-date_time test/tests.cc)
set_target_properties(test-date_time PROPERTIES
                                     CXX_STANDARD 17
                                     CXX_STANDARD_REQUIRED YES
                                     CXX_EXTENSIONS NO)
target_link_libraries(test-date_time date_time Catch2)

enable_testing()
add_test(test-date_time test-date_time)

