#https://cmake.org/cmake-tutorial/
cmake_minimum_required(VERSION 3.12)
project( dataStructures )

set(CMAKE_CXX_STANDARD 17)

set( MAJOR_REV 0 )
set( MINOR_REV 0 )
set( INCIDENTAL_REV 42 )

include_directories( header )
include_directories( catch/single_include )

#aux_source_directory( source source_location )
file( GLOB source_location source/*.cc)

add_executable( main ${source_location} )
