
# no warning
set(NO_WARN_LIST
)

# weak warning level
set(WEAK_MSVC_WARN_LIST
  /W1
)

# gcc/clang shared
set(WEAK_SHARED_WARN_LIST
  -Wall
  -Wextra
  -Wpedantic
)

set(WEAK_GCC_WARN_LIST
)

set(WEAK_CLANG_WARN_LIST
)

set(WEAK_WARN_LIST
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
  "${WEAK_SHARED_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:GNU>:
  "${WEAK_GCC_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:Clang>:
  "${WEAK_CLANG_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:MSVC>:
  "${WEAK_MSVC_WARN_LIST}"
  >
)

# warnings for tests
# doesn't need to be super strong, but a few things are still nice to notice
set(TEST_MSVC_WARN_LIST
  /W2
)

# gcc/clang shared
set(TEST_SHARED_WARN_LIST
  -Wall
  -Wextra
  -Wpedantic
  -Wshadow
  -Wunused
  -Woverloaded-virtual
)

set(TEST_GCC_WARN_LIST
)

set(TEST_CLANG_WARN_LIST
)

set(TEST_WARN_LIST
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
  "${TEST_SHARED_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:GNU>:
  "${TEST_GCC_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:Clang>:
  "${TEST_CLANG_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:MSVC>:
  "${TEST_MSVC_WARN_LIST}"
  >
)

# strong warnings, as much as reasonable
set(STRONG_MSVC_WARN_LIST
  /W4
)

# gcc/clang shared
set(STRONG_SHARED_WARN_LIST
  -Wall
  -Wextra
  -Werror
  -Wpedantic # warn if non-standard C++ is used
  -Wshadow # warn the user if a variable declaration shadows one from a parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
  # catch hard to track down memory errors
  -Wold-style-cast # warn for c-style casts
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual function
  -Wsign-conversion # warn on sign conversions
  -Wnull-dereference # warn if a null dereference is detected
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output (ie printf)
  -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
)

set(STRONG_GCC_WARN_LIST
  -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
  -Wduplicated-cond # warn if if / else chain has duplicated conditions
  -Wduplicated-branches # warn if if / else branches have duplicated code
  -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
  -Wuseless-cast # warn if you perform a cast to the same type
)

set(STRONG_CLANG_WARN_LIST
)

set(STRONG_WARN_LIST
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
  "${STRONG_SHARED_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:GNU>:
  "${STRONG_GCC_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:Clang>:
  "${STRONG_CLANG_WARN_LIST}"
  >
  $<$<CXX_COMPILER_ID:MSVC>:
  "${STRONG_MSVC_WARN_LIST}"
  >
)

function (common_target TARGET warn_list)
  set(CXX_LEVEL 23)

  set(options)
  set(one_value_args)
  set(multi_value_args)
  cmake_parse_arguments(COMMON_TARGET "${options}" "${one_value_args}" "${multi_value_args}")

  get_target_property(type ${TARGET} TYPE)

  if (${type} STREQUAL "INTERFACE_LIBRARY")
    set_target_properties(${TARGET} PROPERTIES
      INTERFACE_CXX_STANDARD ${CXX_LEVEL}
      INTERFACE_CXX_STANDARD_REQUIRED YES)
    target_compile_features(${TARGET}
      INTERFACE
      cxx_std_${CXX_LEVEL})

    target_compile_options(${TARGET}
      INTERFACE
      ${warn_list}
    )
  else ()
    set_target_properties(${TARGET} PROPERTIES
      CXX_STANDARD ${CXX_LEVEL}
      CXX_STANDARD_REQUIRED YES)
    target_compile_features(${TARGET}
      PUBLIC
      cxx_std_${CXX_LEVEL})

    target_compile_options(${TARGET}
      PRIVATE
      ${warn_list}
    )
  endif ()

  set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
endfunction ()

function (common_executable TARGET)
  add_executable(${TARGET}
    ${ARGN}
  )

  common_target(${TARGET} "${STRONG_WARN_LIST}")
endfunction ()

function (common_library TARGET)
  add_library(${TARGET}
    ${ARGN}
  )

  common_target(${TARGET} "${STRONG_WARN_LIST}")
endfunction ()

function (common_test TARGET)
  add_executable(${TARGET}
    ${ARGN}
  )

  common_target(${TARGET} "${TEST_WARN_LIST}")
endfunction ()

function (external_library TARGET)
  add_library(${TARGET}
    ${ARGN}
  )

  # this should maybe be no warn?
  common_target(${TARGET} "${WEAK_WARN_LIST}")
endfunction ()
