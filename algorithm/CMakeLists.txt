CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(algorithms LANGUAGES CXX)

IF(TARGET algorithms)
    RETURN()
ENDIF()

IF(NOT TARGET Catch2)
    ADD_SUBDIRECTORY("../catch/" Catch2)
ENDIF()
IF(NOT TARGET vector)
    #	add_subdirectory("../vector/" vector)
ENDIF()

ADD_LIBRARY(algorithms INTERFACE)

SET_TARGET_PROPERTIES(algorithms PROPERTIES
                      INTERFACE_CXX_STANDARD 17
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

TARGET_INCLUDE_DIRECTORIES(algorithms INTERFACE header)

#target_link_libraries(algorithms INTERFACE vector)
TARGET_LINK_LIBRARIES(algorithms INTERFACE)

ADD_EXECUTABLE(test-algorithms test/tests.cc)
SET_TARGET_PROPERTIES(test-algorithms PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_LINK_LIBRARIES(test-algorithms algorithms Catch2)

ENABLE_TESTING()
ADD_TEST(test-algorithms test-algorithms)

