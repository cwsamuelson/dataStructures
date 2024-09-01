cmake_minimum_required(VERSION 3.21)
GET_FILENAME_COMPONENT(DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
PROJECT(${DIR_NAME})

find_package(galactic_structures REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  PUBLIC
  galactic_structures::galactic_structures
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
)
target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_20
)
