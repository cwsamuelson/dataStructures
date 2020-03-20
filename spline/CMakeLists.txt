CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(spline LANGUAGES CXX)

ADD_LIBRARY(spline source/spline.cc)

SET_TARGET_PROPERTIES(spline PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(spline PUBLIC header)
TARGET_LINK_LIBRARIES(spline PUBLIC polynomial)

ADD_EXECUTABLE(test-spline test/tests.cc)
SET_TARGET_PROPERTIES(test-spline PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-spline spline Catch2)

ENABLE_TESTING()
ADD_TEST(test-spline test-spline)

