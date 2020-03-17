CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(allocator LANGUAGES CXX)

ADD_LIBRARY(allocator INTERFACE)

SET_TARGET_PROPERTIES(allocator PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(allocator INTERFACE header)

ADD_EXECUTABLE(test-allocator test/tests.cc)
SET_TARGET_PROPERTIES(test-allocator PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-allocator allocator Catch2 algorithms)

ENABLE_TESTING()
ADD_TEST(test-allocator test-allocator)

