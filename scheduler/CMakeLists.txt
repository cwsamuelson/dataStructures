cmake_minimum_required(VERSION 3.0)
project(scheduler LANGUAGES CXX)

if(TARGET scheduler)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET unit)
	add_subdirectory("../unit/" unit)
endif()
if(NOT TARGET ratio)
	add_subdirectory("../ratio/" ratio)
endif()

add_library(scheduler INTERFACE)

set_target_properties(scheduler PROPERTIES
                                INTERFACE_CXX_STANDARD 17
                                INTERFACE_CXX_STANDARD_REQUIRED YES
                                INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(scheduler INTERFACE header)
target_link_libraries(scheduler INTERFACE ratio
		                        INTERFACE unit)

add_executable(test-scheduler test/tests.cc)
set_target_properties(test-scheduler PROPERTIES
                                     CXX_STANDARD 17
                                     CXX_STANDARD_REQUIRED YES
                                     CXX_EXTENSIONS NO)
target_link_libraries(test-scheduler scheduler Catch2)

enable_testing()
add_test(test-scheduler test-scheduler)

