cmake_minimum_required(VERSION 3.21)
project(GalacticStructures LANGUAGES CXX)

include(cmake/common.cmake)

common_library(${PROJECT_NAME} INTERFACE)

add_subdirectory(core)
#add_subdirectory(future)
#add_subdirectory(lifetime)
#add_subdirectory(matrix)
#add_subdirectory(normal_iterator)
#add_subdirectory(operators)
#add_subdirectory(optional)
#add_subdirectory(ProducerConsumer)
#add_subdirectory(vector)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${PROJECT_NAME}_core
  #${PROJECT_NAME}_future
  #${PROJECT_NAME}_lifetime
  #${PROJECT_NAME}_matrix
  #${PROJECT_NAME}_normal_iterator
  #${PROJECT_NAME}_operators
  #${PROJECT_NAME}_optional
  #${PROJECT_NAME}_ProducerConsumer
  #${PROJECT_NAME}_vector
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_RPATH "\$ORIGIN/../lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

#install(TARGETS
  #${PROJECT_NAME}_core
  #${PROJECT_NAME}_future
  #${PROJECT_NAME}_lifetime
  #${PROJECT_NAME}_matrix
  #${PROJECT_NAME}_normal_iterator
  #${PROJECT_NAME}_operators
  #${PROJECT_NAME}_optional
  #${PROJECT_NAME}_ProducerConsumer
  #${PROJECT_NAME}_vector
  #)

