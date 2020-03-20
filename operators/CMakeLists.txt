CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(operators LANGUAGES CXX)

ADD_LIBRARY(operators INTERFACE)

SET_TARGET_PROPERTIES(operators PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(operators INTERFACE header)

ADD_EXECUTABLE(test-operators test/tests.cc)
SET_TARGET_PROPERTIES(test-operators PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-operators operators Catch2)

ENABLE_TESTING()
ADD_TEST(test-operators test-operators)

