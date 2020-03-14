CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(vector LANGUAGES CXX)

IF(TARGET vector)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET vector)
    ADD_SUBDIRECTORY("../normal_iterator/" normal_iterator)
ENDIF()
IF(NOT TARGET allocator)
    ADD_SUBDIRECTORY("../allocator/" allocator)
ENDIF()

ADD_LIBRARY(vector INTERFACE)

SET_TARGET_PROPERTIES(vector PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(vector INTERFACE header)

TARGET_LINK_LIBRARIES(vector INTERFACE normal_iterator allocator)

ADD_EXECUTABLE(test-vector test/tests.cc)
SET_TARGET_PROPERTIES(test-vector PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-vector vector Catch2)

ENABLE_TESTING()
ADD_TEST(test-vector test-vector)

