CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(named_point LANGUAGES CXX)

ADD_LIBRARY(named_point INTERFACE)

SET_TARGET_PROPERTIES(named_point PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(named_point INTERFACE header)
TARGET_LINK_LIBRARIES(named_point INTERFACE named_type INTERFACE array)

ADD_EXECUTABLE(test-named_point test/tests.cc)
SET_TARGET_PROPERTIES(test-named_point PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-named_point named_point Catch2)

ENABLE_TESTING()
ADD_TEST(test-named_point test-named_point)

