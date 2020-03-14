CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(skip_list LANGUAGES CXX)

IF(TARGET skip_list)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET normal_iterator)
    ADD_SUBDIRECTORY("../tuple/" normal_iterator)
ENDIF()

ADD_LIBRARY(skip_list INTERFACE)

SET_TARGET_PROPERTIES(skip_list PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(skip_list INTERFACE header)
TARGET_LINK_LIBRARIES(skip_list INTERFACE normal_iterator)

ADD_EXECUTABLE(test-skip_list test/tests.cc)
SET_TARGET_PROPERTIES(test-skip_list PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-skip_list skip_list Catch2)

ENABLE_TESTING()
ADD_TEST(test-skip_list test-skip_list)

