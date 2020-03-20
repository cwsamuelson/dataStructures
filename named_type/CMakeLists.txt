CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(named_type LANGUAGES CXX)

ADD_LIBRARY(named_type INTERFACE)

SET_TARGET_PROPERTIES(named_type PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(named_type INTERFACE header)
TARGET_LINK_LIBRARIES(named_type INTERFACE tuple)

ADD_EXECUTABLE(test-named_type test/tests.cc)
SET_TARGET_PROPERTIES(test-named_type PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-named_type named_type Catch2)

ENABLE_TESTING()
ADD_TEST(test-named_type test-named_type)

