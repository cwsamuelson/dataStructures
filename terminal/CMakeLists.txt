cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_terminal LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/terminal/template.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME}
  INTERFACE
  ${HEADERS}
  ${SOURCES}
)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  BASE_DIRS header
  FILES ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${BASE_PROJECT}_core

  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

if (NOT WIN32)
  common_executable(${PROJECT_NAME}_exe
    source/main.cc
  )

  target_link_libraries(${PROJECT_NAME}_exe
    PUBLIC
    ${PROJECT_NAME}
  )
endif ()