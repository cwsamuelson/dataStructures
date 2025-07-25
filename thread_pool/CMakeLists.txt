cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_thread_pool LANGUAGES CXX)

find_package(error_support REQUIRED)

set(HEADERS
  header/locked_queue.hh
  header/queue.hh
  header/thread_pool.hh
)
set(SOURCES
  source/thread_pool.cc
)

common_library(${PROJECT_NAME}
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
  PUBLIC

  ${BASE_PROJECT}_core
  error_support::error_support
)

if (NOT WIN32)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC
    atomic
  )
endif ()

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

