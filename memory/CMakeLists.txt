CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(memory_pool LANGUAGES CXX)

IF(TARGET memory_pool)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()

ADD_LIBRARY(memory_pool INTERFACE)

SET_TARGET_PROPERTIES(memory_pool PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(memory_pool INTERFACE header)

ADD_EXECUTABLE(test-memory_pool test/tests.cc)
SET_TARGET_PROPERTIES(test-memory_pool PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-memory_pool memory_pool Catch2)

ENABLE_TESTING()
ADD_TEST(test-memory_pool test-memory_pool)

