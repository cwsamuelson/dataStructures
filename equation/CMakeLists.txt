cmake_minimum_required(VERSION 3.0)
project(equation LANGUAGES CXX)

if(TARGET equation)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET algorithms)
	add_subdirectory("../algorithm/" algorithms)
endif()

add_library(equation source/equation.cc)

set_target_properties(equation PROPERTIES
                               INTERFACE_CXX_STANDARD 17
                               INTERFACE_CXX_STANDARD_REQUIRED YES
                               INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(equation PUBLIC header)

add_executable(test-equation test/tests.cc)
set_target_properties(test-equation PROPERTIES
                                    CXX_STANDARD 17
                                    CXX_STANDARD_REQUIRED YES
                                    CXX_EXTENSIONS NO)
target_link_libraries(test-equation equation Catch2 algorithms)

enable_testing()
add_test(test-equation test-equation)

