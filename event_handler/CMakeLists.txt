CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(event_handler LANGUAGES CXX)

ADD_LIBRARY(event_handler INTERFACE)

SET_TARGET_PROPERTIES(event_handler PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(event_handler INTERFACE header)
TARGET_LINK_LIBRARIES(event_handler INTERFACE tuple)

ADD_EXECUTABLE(test-event_handler test/tests.cc)
SET_TARGET_PROPERTIES(test-event_handler PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-event_handler event_handler Catch2)

ENABLE_TESTING()
ADD_TEST(test-event_handler test-event_handler)

