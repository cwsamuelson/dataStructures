find_package(Git REQUIRED)

execute_process(
  COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --long --always --match "v*"
  OUTPUT_VARIABLE DESCRIPTION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX MATCH "^v([0-9]+\\.[0-9]+\\.[0-9]+)-([0-9]+)-g([0-9a-f]+)(-dirty)?$"
  testing
  ${DESCRIPTION}
)
set(GIT_TAG ${CMAKE_MATCH_1})
set(GIT_DISTANCE ${CMAKE_MATCH_2})
set(GIT_SHORT_HASH ${CMAKE_MATCH_3}) # currently don't care about this; unused
set(GIT_DIRTY ${CMAKE_MATCH_4})

execute_process(
  COMMAND ${GIT_EXECUTABLE} branch --show-current
  OUTPUT_VARIABLE BRANCH_NAME
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND ${GIT_EXECUTABLE} rev-parse --verify HEAD
  OUTPUT_VARIABLE GIT_FULL_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if ("${CI_BUILD_ID}" STREQUAL "")
  set(CI_BUILD_ID "local")
endif()

# if the major version is empty, then we are not building via conan
# so long as a git version can be parsed, this won't be a problem
#! @TODO may be valuable to indicate whether it was a conan or manual build
# the version information should be the same either way, so it shouldn't matter
if (NOT DEFINED VERSION_MAJOR OR VERSION_MAJOR STREQUAL "")
  string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$"
    testing
    ${GIT_TAG}
  )
  # if testing is empty, the match failed
  set(VERSION_MAJOR ${MAKE_MATCH_1})
  set(VERSION_MINOR ${MAKE_MATCH_2})
  set(VERSION_PATCH ${MAKE_MATCH_3})
endif()

# if the generated file is the same as the existing file, the file is not actually written
# this prevents spurious rebuilds when no version information has changed
configure_file(${SRC} ${SDST})
configure_file(${HDR} ${HDST})

