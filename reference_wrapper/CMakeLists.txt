CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(reference_wrapper LANGUAGES CXX)

ADD_LIBRARY(reference_wrapper INTERFACE)

SET_TARGET_PROPERTIES(reference_wrapper PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(reference_wrapper INTERFACE header)
TARGET_LINK_LIBRARIES(reference_wrapper INTERFACE tuple)

ADD_EXECUTABLE(test-reference_wrapper test/tests.cc)
SET_TARGET_PROPERTIES(test-reference_wrapper PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-reference_wrapper reference_wrapper Catch2)

ENABLE_TESTING()
ADD_TEST(test-reference_wrapper test-reference_wrapper)

