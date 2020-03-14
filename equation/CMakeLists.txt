CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(equation LANGUAGES CXX)

IF(TARGET equation)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET algorithms)
    ADD_SUBDIRECTORY("../algorithm/" algorithms)
ENDIF()

ADD_LIBRARY(equation source/equation.cc)

SET_TARGET_PROPERTIES(equation PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(equation PUBLIC header)

ADD_EXECUTABLE(test-equation test/tests.cc)
SET_TARGET_PROPERTIES(test-equation PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-equation equation Catch2 algorithms)

ENABLE_TESTING()
ADD_TEST(test-equation test-equation)

