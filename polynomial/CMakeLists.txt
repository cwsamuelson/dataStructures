CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(polynomial LANGUAGES CXX)

ADD_LIBRARY(polynomial source/polynomial.cc source/high_polynomial.cc)

SET_TARGET_PROPERTIES(polynomial PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(polynomial PUBLIC header)
TARGET_LINK_LIBRARIES(polynomial PUBLIC operators PUBLIC named_point)

ADD_EXECUTABLE(test-polynomial test/tests.cc)
SET_TARGET_PROPERTIES(test-polynomial PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-polynomial polynomial algorithms Catch2)

ENABLE_TESTING()
ADD_TEST(test-polynomial test-polynomial)

