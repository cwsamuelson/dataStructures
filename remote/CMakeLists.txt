CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(remote LANGUAGES CXX)

IF(TARGET remote)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()

ADD_LIBRARY(remote INTERFACE)

SET_TARGET_PROPERTIES(remote PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(remote INTERFACE header)
#target_link_libraries(remote INTERFACE tuple)

ADD_EXECUTABLE(test-remote test/tests.cc)
SET_TARGET_PROPERTIES(test-remote PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-remote remote Catch2)

ENABLE_TESTING()
ADD_TEST(test-remote test-remote)

