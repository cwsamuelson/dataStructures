CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(normal_iterator LANGUAGES CXX)

IF(TARGET normal_iterator)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET operators)
    ADD_SUBDIRECTORY("../operators/" operators)
ENDIF()

ADD_LIBRARY(normal_iterator INTERFACE)

SET_TARGET_PROPERTIES(normal_iterator PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(normal_iterator INTERFACE header)

TARGET_LINK_LIBRARIES(normal_iterator INTERFACE operators)

ENABLE_TESTING()

ADD_EXECUTABLE(test-normal_iterator test/tests.cc)
SET_TARGET_PROPERTIES(test-normal_iterator PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-normal_iterator normal_iterator Catch2)
ADD_TEST(test-normal_iterator test-normal_iterator)

