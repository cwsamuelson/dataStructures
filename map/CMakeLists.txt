CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(map LANGUAGES CXX)

ADD_LIBRARY(map INTERFACE)

SET_TARGET_PROPERTIES(map PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(map INTERFACE header)
TARGET_LINK_LIBRARIES(map INTERFACE normal_iterator
                      INTERFACE vector
                      INTERFACE tuple
                      INTERFACE allocator)

ADD_EXECUTABLE(test-map test/tests.cc)
SET_TARGET_PROPERTIES(test-map PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-map map Catch2)

ENABLE_TESTING()
ADD_TEST(test-map test-map)

