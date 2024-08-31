find_package(antlr4-runtime REQUIRED)
find_package(Java REQUIRED)

# download antlr parser generator
set(antlr_jar_name "antlr-4.13.1-complete.jar")
set(antlr_binary "${CMAKE_BINARY_DIR}/${antlr_jar_name}")
if (NOT EXISTS "${antlr_binary}")
  message(STATUS "Downloading antlr tool")
  file(DOWNLOAD https://www.antlr.org/download/${antlr_jar_name} ${antlr_binary})
endif ()

function (print_sources TARGET MESSAGE)
  get_target_property(_source_list ${TARGET} SOURCES)
  message(STATUS "-------------------------- FILE LIST (${TARGET}) ${MESSAGE}")
  foreach (_file ${_source_list})
    message(STATUS "${_file}")
  endforeach ()
endfunction ()

function (antlr_generate TARGET PACKAGE)
  get_target_property(SOURCE_LIST ${TARGET} SOURCES)
  list(FILTER SOURCE_LIST INCLUDE REGEX "g4$")

  foreach (_file ${SOURCE_LIST})
    get_filename_component(abs_file_path "${_file}" REALPATH)
    list(APPEND antlr_generate_g4 ${abs_file_path})
  endforeach ()

  foreach (g4_file ${antlr_generate_g4})
    file(READ "${g4_file}" g4_content)

    string(REGEX MATCH "^lexer.*$" lex_match "${g4_content}")
    string(REGEX REPLACE "g4$" "cpp" cpp_source ${g4_file})
    string(REGEX REPLACE ".*[/\\](.*).cpp$" "${CMAKE_BINARY_DIR}/generated/${TARGET}/\\1.cpp" cc_source ${cpp_source})

    list(APPEND antlr4-GENERATED_SRC "${cc_source}")

    if ("${lex_match}" STREQUAL "")
      string(REGEX REPLACE ".*[/\\](.*).g4$" "${CMAKE_BINARY_DIR}/generated/${TARGET}/\\1BaseListener.cpp" new_source ${g4_file})
      list(APPEND antlr4-GENERATED_SRC ${new_source})
      string(REGEX REPLACE ".*[/\\](.*).g4$" "${CMAKE_BINARY_DIR}/generated/${TARGET}/\\1BaseVisitor.cpp" new_source ${g4_file})
      list(APPEND antlr4-GENERATED_SRC ${new_source})
      string(REGEX REPLACE ".*[/\\](.*).g4$" "${CMAKE_BINARY_DIR}/generated/${TARGET}/\\1Listener.cpp" new_source ${g4_file})
      list(APPEND antlr4-GENERATED_SRC ${new_source})
      string(REGEX REPLACE ".*[/\\](.*).g4$" "${CMAKE_BINARY_DIR}/generated/${TARGET}/\\1Visitor.cpp" new_source ${g4_file})
      list(APPEND antlr4-GENERATED_SRC ${new_source})
    endif ()
  endforeach ()

  foreach (src_file ${antlr4-GENERATED_SRC})
    set_source_files_properties(
      ${src_file}
      PROPERTIES
      GENERATED TRUE
    )
  endforeach (src_file ${antlr4-GENERATED_SRC})

  # CMAKE_BINARY_DIR or CMAKE_CURRENT_BINARY_DIR ?
  add_custom_command(OUTPUT ${antlr4-GENERATED_SRC}
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/generated
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/generated/${TARGET}
    COMMAND
    "${Java_JAVA_EXECUTABLE}" -jar ${antlr_binary} -Werror -Dlanguage=Cpp -listener -visitor -o ${CMAKE_BINARY_DIR}/generated/${TARGET} -package ${PACKAGE} ${antlr_generate_g4}
    #WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/generated"
    DEPENDS ${antlr_generate_g4}
  )

  target_sources(${TARGET}
    PRIVATE
    ${antlr4-GENERATED_SRC}
  )

  target_include_directories(${TARGET}
    PUBLIC
    ${CMAKE_BINARY_DIR}/generated/${TARGET}
  )

  target_link_libraries(${TARGET}
    PUBLIC
    antlr4_static
  )
endfunction ()
