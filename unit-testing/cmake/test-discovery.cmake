function(discover_tests TARGET)
  set(options
  )
  set(single_value_args
  )
  set(multi_value_args
  )

  cmake_parse_arguments(
    "" # Prefix is appendend with '_'; empty prefix == '_'
    "${options}" # options
    "${single_value_args}" # single value
    "${multi_value_args}" # multi value
    ${ARGN}
  )

  set(suffix "TESTSTUFF")

  set(ctest_base "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}-${suffix}")
  set(ctest_include_file "${ctest_base}_include.cmake")
  set(ctest_tests_file "${ctest_base}_tests.cmake")

  add_custom_command(
    TARGET ${TARGET} POST_BUILD
    BYPRODUCTS "${ctest_tests_file}"
    COMMAND ${CMAKE_COMMAND}
      -D "CTEST_FILE=${ctest_tests_file}"
      -D "TEST_EXECUTABLE=$<TARGET_FILE:${TARGET}>"
      -D "WORKING_DIR=${CMAKE_CURRENT_BINARY_DIR}"
      -P ${add_test_script}
  )

  file(WRITE "${ctest_include_file}"
    "if (EXISTS \"${ctest_tests_file}\")\n"
    "  include(\"${ctest_tests_file}\")\n"
    "else()\n"
    "  add_test(${TARGET} ${TARGET})\n"
    "endif ()\n"
  )

  set_property(DIRECTORY
    APPEND PROPERTY TEST_INCLUDE_FILES "${ctest_include_file}"
  )
endfunction()

set(add_test_script ${CMAKE_CURRENT_LIST_DIR}/add-tests.cmake CACHE INTERNAL "")
