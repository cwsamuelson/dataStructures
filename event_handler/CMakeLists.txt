CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(event_handler LANGUAGES CXX)

FIND_PACKAGE(Threads REQUIRED)

ADD_LIBRARY(event_handler header/signal.hh header/event_handler.hh)

SET_TARGET_PROPERTIES(event_handler PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO
                      LINKER_LANGUAGE CXX)

TARGET_INCLUDE_DIRECTORIES(event_handler PUBLIC header)

TARGET_LINK_LIBRARIES(event_handler PUBLIC Threads::Threads)

ADD_EXECUTABLE(test-event_handler test/events.cc test/signals.cc)
SET_TARGET_PROPERTIES(test-event_handler PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO
                      LINKER_LANGUAGE CXX)
TARGET_LINK_LIBRARIES(test-event_handler event_handler Catch2)

ENABLE_TESTING()
ADD_TEST(test-event_handler test-event_handler)

