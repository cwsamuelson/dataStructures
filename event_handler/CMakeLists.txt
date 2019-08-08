cmake_minimum_required(VERSION 3.0)
project(event_handler LANGUAGES CXX)

if(TARGET event_handler)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET tuple)
	add_subdirectory("../tuple/" tuple)
endif()

add_library(event_handler INTERFACE)

set_target_properties(event_handler PROPERTIES
                                    INTERFACE_CXX_STANDARD 17
                                    INTERFACE_CXX_STANDARD_REQUIRED YES
                                    INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(event_handler INTERFACE .)
target_link_libraries(event_handler INTERFACE tuple)

add_executable(test-event_handler tests.cc)
set_target_properties(test-event_handler PROPERTIES
                                         CXX_STANDARD 17
                                         CXX_STANDARD_REQUIRED YES
                                         CXX_EXTENSIONS NO)
target_link_libraries(test-event_handler event_handler Catch2)

enable_testing()
add_test(test-event_handler test-event_handler)

