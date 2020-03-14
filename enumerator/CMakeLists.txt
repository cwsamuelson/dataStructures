CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(enumerator LANGUAGES CXX)

IF(TARGET enumerator)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()

ADD_LIBRARY(enumerator INTERFACE)

SET_TARGET_PROPERTIES(enumerator PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)
TARGET_INCLUDE_DIRECTORIES(enumerator INTERFACE header)

ADD_EXECUTABLE(test-enumerator test/tests.cc)
SET_TARGET_PROPERTIES(test-enumerator PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-enumerator enumerator Catch2)

ENABLE_TESTING()
ADD_TEST(test-enumerator test-enumerator)

