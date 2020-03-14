CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(scheduler LANGUAGES CXX)

IF(TARGET scheduler)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET unit)
    ADD_SUBDIRECTORY("../unit/" unit)
ENDIF()
IF(NOT TARGET ratio)
    ADD_SUBDIRECTORY("../ratio/" ratio)
ENDIF()

ADD_LIBRARY(scheduler INTERFACE)

SET_TARGET_PROPERTIES(scheduler PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(scheduler INTERFACE header)
TARGET_LINK_LIBRARIES(scheduler INTERFACE ratio
                      INTERFACE unit)

ADD_EXECUTABLE(test-scheduler test/tests.cc)
SET_TARGET_PROPERTIES(test-scheduler PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-scheduler scheduler Catch2)

ENABLE_TESTING()
ADD_TEST(test-scheduler test-scheduler)

