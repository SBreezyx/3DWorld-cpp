cmake_minimum_required(VERSION 3.14)
project("3DWorld (C++)")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(main "")
#add_custom_target(main PU)
target_sources(main PUBLIC src/main.cpp)
target_include_directories(main PUBLIC include)
