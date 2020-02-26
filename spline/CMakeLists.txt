cmake_minimum_required(VERSION 3.0)
project(spline LANGUAGES CXX)

if(TARGET spline)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET polynomial)
	add_subdirectory("polynomial" polynomial)
endif()

add_library(spline source/spline.cc)

set_target_properties(spline PROPERTIES
                             INTERFACE_CXX_STANDARD 17
                             INTERFACE_CXX_STANDARD_REQUIRED YES
                             INTERFACE_CXX_EXTENSIONS NO)

target_include_directories(spline PUBLIC header)
target_link_libraries(spline PRIVATE polynomial)

add_executable(test-spline test/tests.cc)
set_target_properties(test-spline PROPERTIES
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED YES
                                  CXX_EXTENSIONS NO)
target_link_libraries(test-spline spline Catch2)

enable_testing()
add_test(test-spline test-spline)

