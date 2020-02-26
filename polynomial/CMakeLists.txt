cmake_minimum_required(VERSION 3.0)
project(polynomial LANGUAGES CXX)

if(TARGET polynomial)
	return()
endif()

if(NOT TARGET Catch2)
	add_subdirectory("../catch/" Catch2)
endif()
if(NOT TARGET operators)
	add_subdirectory("../tuple/" operators)
endif()
if(NOT TARGET named_point)
	add_subdirectory("../tuple/" named_point)
endif()
if(NOT TARGET algorithm)
	add_subdirectory("../algorithm/" algorithm)
endif()

add_library(polynomial source/polynomial.cc source/high_polynomial.cc)

set_target_properties(polynomial PROPERTIES
                                 CXX_STANDARD 17
                                 CXX_STANDARD_REQUIRED YES
                                 CXX_EXTENSIONS NO)

target_include_directories(polynomial PUBLIC header)
target_link_libraries(polynomial PUBLIC operators PUBLIC named_point)

add_executable(test-polynomial test/tests.cc)
set_target_properties(test-polynomial PROPERTIES
                                      CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED YES
                                      CXX_EXTENSIONS NO)
target_link_libraries(test-polynomial polynomial algorithms Catch2)

enable_testing()
add_test(test-polynomial test-polynomial)

