cmake_minimum_required(VERSION 3.17)
project("3DWorld (C++)")

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

find_package(gsl-lite CONFIG REQUIRED)
add_compile_options(${CMAKE_CXX_FLAGS} -EHa)

add_subdirectory(lib)
add_subdirectory(src)
