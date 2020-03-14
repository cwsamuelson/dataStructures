CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(matrix LANGUAGES CXX)

IF(TARGET matrix)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET operators)
    ADD_SUBDIRECTORY("../operators/" operators)
ENDIF()
IF(NOT TARGET normal_iterator)
    ADD_SUBDIRECTORY("../normal_iterator/" normal_iterator)
ENDIF()

ADD_LIBRARY(matrix INTERFACE)

SET_TARGET_PROPERTIES(matrix PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(matrix INTERFACE header)
TARGET_LINK_LIBRARIES(matrix INTERFACE tuple)

ADD_EXECUTABLE(test-matrix test/tests.cc)
SET_TARGET_PROPERTIES(test-matrix PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-matrix matrix Catch2)

ENABLE_TESTING()
ADD_TEST(test-matrix test-matrix)

