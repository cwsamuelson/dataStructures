cmake_minimum_required(VERSION 3.0)
project(algorithms LANGUAGES CXX)

if(TARGET algorithms)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET vector)
#	add_subdirectory("../vector/" vector)
endif()

add_library(algorithms INTERFACE)

set_target_properties(algorithms PROPERTIES
                                 INTERFACE_CXX_STANDARD 17
                                 INTERFACE_CXX_STANDARD_REQUIRED YES
                                 INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(algorithms INTERFACE .)

#target_link_libraries(algorithms INTERFACE vector)
target_link_libraries(algorithms INTERFACE)

add_executable(test-algorithms tests.cc)
set_target_properties(test-algorithms PROPERTIES
                                      CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED YES
                                      CXX_EXTENSIONS NO)
target_link_libraries(test-algorithms algorithms Catch2)

enable_testing()
add_test(test-algorithms test-algorithms)

