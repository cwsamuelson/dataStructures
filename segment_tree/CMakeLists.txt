CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(segment_tree LANGUAGES CXX)

ADD_LIBRARY(segment_tree INTERFACE)

SET_TARGET_PROPERTIES(segment_tree PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(segment_tree INTERFACE header)

ADD_EXECUTABLE(test-segment_tree test/tests.cc)
SET_TARGET_PROPERTIES(test-segment_tree PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-segment_tree segment_tree Catch2)

ENABLE_TESTING()
ADD_TEST(test-segment_tree test-segment_tree)

