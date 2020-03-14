CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(date_time LANGUAGES CXX)

IF(TARGET date_time)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET unit)
    ADD_SUBDIRECTORY("../unit/" unit)
ENDIF()

ADD_LIBRARY(date_time INTERFACE)

SET_TARGET_PROPERTIES(date_time PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(date_time INTERFACE header)
TARGET_LINK_LIBRARIES(date_time INTERFACE unit)

ADD_EXECUTABLE(test-date_time test/tests.cc)
SET_TARGET_PROPERTIES(test-date_time PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-date_time date_time Catch2)

ENABLE_TESTING()
ADD_TEST(test-date_time test-date_time)

