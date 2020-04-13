CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(regex LANGUAGES CXX)

ADD_LIBRARY(regex source/regex.cc header/regex.hh)

SET_TARGET_PROPERTIES(regex PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(regex PUBLIC header)

ADD_EXECUTABLE(test-regex test/tests.cc)
SET_TARGET_PROPERTIES(test-regex PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-regex regex Catch2)

ENABLE_TESTING()
ADD_TEST(test-regex test-regex)

