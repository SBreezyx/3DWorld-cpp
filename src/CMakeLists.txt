add_executable(main)
target_sources(main PUBLIC main.cpp)
target_include_directories(main PUBLIC include)
target_link_libraries(main glfw3 glad range-v3)