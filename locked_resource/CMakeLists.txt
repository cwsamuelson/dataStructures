CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(locked_resource LANGUAGES CXX)

IF(TARGET locked_resource)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()

FIND_PACKAGE(Threads REQUIRED)

ADD_LIBRARY(locked_resource INTERFACE)

SET_TARGET_PROPERTIES(locked_resource PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(locked_resource INTERFACE header)
TARGET_LINK_LIBRARIES(locked_resource INTERFACE Threads::Threads)

ADD_EXECUTABLE(test-locked_resource test/tests.cc)
SET_TARGET_PROPERTIES(test-locked_resource PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-locked_resource locked_resource Catch2)

ENABLE_TESTING()
ADD_TEST(test-locked_resource test-locked_resource)

