cmake_minimum_required(VERSION 3.21)
project(GalacticStructures LANGUAGES CXX)

find_package(cmake_scripts REQUIRED)

add_subdirectory(aligned_buffer)
add_subdirectory(context)
add_subdirectory(core)
add_subdirectory(future)
add_subdirectory(hive)
add_subdirectory(lifetime)
add_subdirectory(matrix)
#add_subdirectory(normal_iterator)
#add_subdirectory(operators)
add_subdirectory(optional)
add_subdirectory(polynomial)
add_subdirectory(producer_consumer)
add_subdirectory(ranged_int)
add_subdirectory(std_hive)
add_subdirectory(units)
add_subdirectory(vector)

common_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${PROJECT_NAME}_aligned_buffer
  ${PROJECT_NAME}_core
  ${PROJECT_NAME}_context
  ${PROJECT_NAME}_future
  ${PROJECT_NAME}_hive
  ${PROJECT_NAME}_lifetime
  ${PROJECT_NAME}_matrix
  #${PROJECT_NAME}_normal_iterator
  #${PROJECT_NAME}_operators
  ${PROJECT_NAME}_optional
  ${PROJECT_NAME}_polynomial
  ${PROJECT_NAME}_producer_consumer
  ${PROJECT_NAME}_ranged_int
  ${PROJECT_NAME}_std_hive
  ${PROJECT_NAME}_units
  ${PROJECT_NAME}_vector
)

enable_testing()

