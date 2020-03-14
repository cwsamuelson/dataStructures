CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(function LANGUAGES CXX)

IF(TARGET function)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()

ADD_LIBRARY(function INTERFACE)

SET_TARGET_PROPERTIES(function PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(function INTERFACE header)
TARGET_LINK_LIBRARIES(function INTERFACE tuple)

ADD_EXECUTABLE(test-function test/tests.cc)
SET_TARGET_PROPERTIES(test-function PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-function function Catch2)

ENABLE_TESTING()
ADD_TEST(test-function test-function)

