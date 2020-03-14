CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(prefix_tree LANGUAGES CXX)

IF(TARGET prefix_tree)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()

ADD_LIBRARY(prefix_tree INTERFACE)

SET_TARGET_PROPERTIES(prefix_tree PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(prefix_tree INTERFACE header)
TARGET_LINK_LIBRARIES(prefix_tree INTERFACE tuple)

ADD_EXECUTABLE(test-prefix_tree test/tests.cc)
SET_TARGET_PROPERTIES(test-prefix_tree PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-prefix_tree prefix_tree Catch2)

ENABLE_TESTING()
ADD_TEST(test-prefix_tree test-prefix_tree)

