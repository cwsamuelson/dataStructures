cmake_minimum_required(VERSION 3.21)
set(BASE_PROJECT ${PROJECT_NAME})
project(${BASE_PROJECT}_core LANGUAGES CXX)

set(HEADERS
        header/core/additive.hh
        header/core/comparative.hh
        header/core/concepts.hh
        header/core/maybe_const.hh
        header/core/multiplicative.hh
        header/core/normal_iterator.hh
        header/core/operators.hh
        header/core/overloads.hh
        header/core/range.hh
        header/core/tagged_type.hh
        header/core/traits.hh
        header/core/traits/const.hh
        header/core/traits/function.hh
        header/core/traits/impl/const.hh
        header/core/traits/impl/pointer.hh
        header/core/traits/impl/reference.hh
        header/core/traits/impl/volatile.hh
        header/core/traits/integral.hh
        header/core/traits/pointer.hh
        header/core/traits/reference.hh
        header/core/traits/value_types.hh
        header/core/traits/volatile.hh
)
set(SOURCES
)

common_library(${PROJECT_NAME} INTERFACE
        ${HEADERS}
        ${SOURCES}
)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS header
        FILES ${HEADERS}
)

install(TARGETS ${PROJECT_NAME} FILE_SET public_headers)

enable_testing()
add_subdirectory(test)

