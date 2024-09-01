cmake_minimum_required(VERSION 3.21)
project(GalacticStructures LANGUAGES CXX)

include(cmake/common.cmake)

add_subdirectory(aligned_buffer)
add_subdirectory(core)
#add_subdirectory(future)
#add_subdirectory(lifetime)
#add_subdirectory(matrix)
#add_subdirectory(normal_iterator)
#add_subdirectory(operators)
#add_subdirectory(optional)
#add_subdirectory(ProducerConsumer)
add_subdirectory(vector)

common_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${PROJECT_NAME}_aligned_buffer
  ${PROJECT_NAME}_core
  #${PROJECT_NAME}_future
  #${PROJECT_NAME}_lifetime
  #${PROJECT_NAME}_matrix
  #${PROJECT_NAME}_normal_iterator
  #${PROJECT_NAME}_operators
  #${PROJECT_NAME}_optional
  #${PROJECT_NAME}_ProducerConsumer
  ${PROJECT_NAME}_vector
)

enable_testing()

