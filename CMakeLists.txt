cmake_minimum_required ( VERSION 3.1.0...3.27.0 )

project ( RTWeekend LANGUAGES CXX )


# Set to C++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

# Add source files
set(SOURCES
    src/main.cpp
    src/vec3.h
    src/color.h
)

include_directories(src) # for include .h files

add_compile_options(
    -Wnon-virtual-dtor # Class has virtual functions, but its destructor is not virtual
    -Wreorder # Data member will be initialized after [other] data member
    -Wmaybe-uninitialized # Variable improperly initialized
    -Wunused-variable # Variable is defined but unused
)

# Add executable
add_executable(RTWeekend ${SOURCES})