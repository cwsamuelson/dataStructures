CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(string LANGUAGES CXX)

ADD_LIBRARY(string INTERFACE)

SET_TARGET_PROPERTIES(string PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(string INTERFACE header)
TARGET_LINK_LIBRARIES(string INTERFACE tuple
                      INTERFACE allocator
                      INTERFACE normal_iterator)

ADD_EXECUTABLE(test-string test/tests.cc)
SET_TARGET_PROPERTIES(test-string PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-string string Catch2)

ENABLE_TESTING()
ADD_TEST(test-string test-string)

