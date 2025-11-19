function(add_command NAME)
  set(args "")

  math(EXPR last_index ${ARGC}-1)
  foreach(index RANGE 1 ${last_index})
    set(arg "${ARGV${index}}")

    if (arg MATCHES "[^-./:a-zA-Z0-9_]")
      set(args "${args} [==[${arg}]==]")
    else()
      set(args "${args} ${arg}")
    endif()
  endforeach()

  set(script "${script}${NAME}(${args})\n" PARENT_SCOPE)
endfunction()

function(discover_tests_impl)
  set(options
  )
  set(single_value_args
    CTEST_FILE
    TEST_EXECUTABLE
    WORKING_DIR
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

  if (NOT EXISTS "${_TEST_EXECUTABLE}")
    message(FATAL_ERROR "Test executable (${_TEST_EXECUTABLE}) does not exist.")
  endif()

  set(script )
  set(tests )

  execute_process(
    COMMAND "${_TEST_EXECUTABLE}" --list-tests
    OUTPUT_VARIABLE test_output
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${_WORKING_DIR}"
  )

  if (NOT ${result} EQUAL 0)
    message(FATAL_ERROR
      "Error listing tests from executable ${_TEST_EXECUTABLE}.\n"
      "\tProgram returned: ${result}"
      "\tProgram reported: ${test_output}"
    )
  endif()

  message(STATUS "output: ${test_output}")
  string(JSON version GET "${test_output}" "version")
  if (NOT ${version} EQUAL 1)
    message(FATAL_ERROR "Unsupported output format version: ${version}")
  endif()

  string(JSON tests_list GET "${test_output}" "tests")
  string(JSON test_count LENGTH "${tests_list}")

  if (test_count STREQUAL "0")
    message(WARNING "No tests found for ${_TEST_EXECUTABLE}")
    return()
  endif()

  math(EXPR last_index ${test_count}-1)
  foreach(index RANGE ${last_index})
    string(JSON test_name GET "${tests_list}" ${index})

    # parse/handle escape characters etc that might otherwise cause weird issues

    add_command(
      add_test
      "${test_name}"
      "${_TEST_EXECUTABLE}"
      "${test_name}"
    )
    add_command(
      set_tests_properties
      "${test_name}"
      PROPERTIES
      WORKING_DIRECTORY "${_WORKING_DIR}"
    )

    list(APPEND tests "${test_name}")
  endforeach()

  add_command(set ${_TEST_LIST} ${tests})

  file(WRITE "${_CTEST_FILE}" "${script}")
endfunction()

discover_tests_impl(
  CTEST_FILE ${CTEST_FILE}
  TEST_EXECUTABLE ${TEST_EXECUTABLE}
  WORKING_DIR ${WORKING_DIR}
)
