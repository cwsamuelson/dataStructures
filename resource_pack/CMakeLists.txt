set(BASE_PROJECT ${PROJECT_NAME})
GET_FILENAME_COMPONENT(DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${BASE_PROJECT}_${DIR_NAME} LANGUAGES CXX)

find_package(error_support REQUIRED)

set(SOURCE_FILES
  source/resource_pack.cc
)
set(HEADER_FILES
  header/pack/resource_pack.hh
)

common_library(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES}
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
  error_support::error_support
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

