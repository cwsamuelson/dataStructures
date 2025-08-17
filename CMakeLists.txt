cmake_minimum_required(VERSION 3.21)
project(GalacticStructures LANGUAGES CXX)

set(CONAN_CMAKE_SILENT_OUTPUT TRUE CACHE BOOL "")

find_package(cmake_scripts REQUIRED)

add_subdirectory(aligned_buffer)
add_subdirectory(box)
add_subdirectory(colors)
add_subdirectory(configuration)
add_subdirectory(context)
add_subdirectory(coordinates)
add_subdirectory(core)
add_subdirectory(curryable)
add_subdirectory(delegate)
add_subdirectory(doubly_linked_list)
#add_subdirectory(ecs)
#add_subdirectory(equation)
#add_subdirectory(expr_template)
add_subdirectory(function)
add_subdirectory(future)
add_subdirectory(hive)
add_subdirectory(inplace_vector)
#add_subdirectory(lifetime)
add_subdirectory(matrix)
#add_subdirectory(normal_iterator)
#add_subdirectory(operators)
add_subdirectory(optional)
#add_subdirectory(polymorphic_value)
add_subdirectory(polynomial)
add_subdirectory(process_manager)
add_subdirectory(producer_consumer)
add_subdirectory(property)
add_subdirectory(ranged_int)
add_subdirectory(ratio)
add_subdirectory(resource_pack)
add_subdirectory(ring_buffer)
add_subdirectory(ring_view)
#add_subdirectory(scheduler)
add_subdirectory(singly_linked_list)
add_subdirectory(shared_ptr)
add_subdirectory(sparse_map)
add_subdirectory(sparse_set)
#add_subdirectory(std_hive)
#add_subdirectory(sum_type)
add_subdirectory(thread_pool)
add_subdirectory(tribool)
add_subdirectory(try_wrap)
add_subdirectory(type_pack)
add_subdirectory(type_set)
#add_subdirectory(units)
#add_subdirectory(utilities)
add_subdirectory(value_pack)
add_subdirectory(value_set)
add_subdirectory(vector)
#add_subdirectory(versioning)

common_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  ${PROJECT_NAME}_aligned_buffer
  ${PROJECT_NAME}_box
  ${PROJECT_NAME}_colors
  ${PROJECT_NAME}_configuration
  ${PROJECT_NAME}_context
  ${PROJECT_NAME}_coordinates
  ${PROJECT_NAME}_core
  ${PROJECT_NAME}_curryable
  ${PROJECT_NAME}_delegate
  ${PROJECT_NAME}_doubly_linked_list
  #${PROJECT_NAME}_ecs
  #${PROJECT_NAME}_equation
  #${PROJECT_NAME}_expr_template
  ${PROJECT_NAME}_function
  ${PROJECT_NAME}_future
  ${PROJECT_NAME}_hive
  ${PROJECT_NAME}_inplace_vector
  #${PROJECT_NAME}_lifetime
  ${PROJECT_NAME}_matrix
  #${PROJECT_NAME}_normal_iterator
  #${PROJECT_NAME}_operators
  ${PROJECT_NAME}_optional
  #${PROJECT_NAME}_polymorphic_value
  ${PROJECT_NAME}_polynomial
  ${PROJECT_NAME}_process_manager
  ${PROJECT_NAME}_producer_consumer
  ${PROJECT_NAME}_property
  ${PROJECT_NAME}_ranged_int
  ${PROJECT_NAME}_ratio
  ${PROJECT_NAME}_resource_pack
  ${PROJECT_NAME}_ring_buffer
  ${PROJECT_NAME}_ring_view
  #${PROJECT_NAME}_scheduler
  ${PROJECT_NAME}_singly_linked_list
  ${PROJECT_NAME}_shared_ptr
  ${PROJECT_NAME}_sparse_map
  ${PROJECT_NAME}_sparse_set
  #${PROJECT_NAME}_std_hive
  #${PROJECT_NAME}_sum_type
  ${PROJECT_NAME}_thread_pool
  ${PROJECT_NAME}_tribool
  ${PROJECT_NAME}_try_wrap
  ${PROJECT_NAME}_type_pack
  ${PROJECT_NAME}_type_set
  #${PROJECT_NAME}_units
  #${PROJECT_NAME}_utilities
  ${PROJECT_NAME}_value_pack
  ${PROJECT_NAME}_value_set
  ${PROJECT_NAME}_vector
  #${PROJECT_NAME}_versioning
)

enable_testing()

