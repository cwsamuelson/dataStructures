CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(array LANGUAGES CXX)

IF(TARGET array)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET normal_iterator)
    ADD_SUBDIRECTORY("../normal_iterator/" normal_iterator)
ENDIF()

ADD_LIBRARY(array INTERFACE)

SET_TARGET_PROPERTIES(array PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(array INTERFACE header)
TARGET_LINK_LIBRARIES(array INTERFACE normal_iterator)

ADD_EXECUTABLE(test-array test/tests.cc)
SET_TARGET_PROPERTIES(test-array PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-array array Catch2)

ENABLE_TESTING()
ADD_TEST(test-array test-array)

