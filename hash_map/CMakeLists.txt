CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(hash_map LANGUAGES CXX)

ADD_LIBRARY(hash_map INTERFACE)

SET_TARGET_PROPERTIES(hash_map PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(hash_map INTERFACE header)
TARGET_LINK_LIBRARIES(hash_map INTERFACE normal_iterator
                      INTERFACE allocator)

ADD_EXECUTABLE(test-hash_map test/tests.cc)
SET_TARGET_PROPERTIES(test-hash_map PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-hash_map hash_map Catch2)

ENABLE_TESTING()
ADD_TEST(test-hash_map test-hash_map)

