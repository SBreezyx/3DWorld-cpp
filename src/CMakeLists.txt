add_executable(main)
target_sources(main
        PUBLIC
        main.cpp window.cpp
        ${PROJECT_INCLUDE_DIR}/sys/window.hpp
        )

target_include_directories(main
        PUBLIC
        ${PROJECT_INCLUDE_DIR}
        )

target_link_libraries(main PUBLIC glad glfw range-v3 fmt gsl::gsl-lite)

target_compile_options(main PUBLIC
        ${CMAKE_CXX_FLAGS}
        -Werror
        -W4
        -Wextra
        -Wcast-align
        -Wconversion
        -Wdouble-promotion
        -Wold-style-cast
        -Woverloaded-virtual
        -Wshadow
        -Wsign-promo
        -Wno-sign-conversion
        -Wunused
        -Wodr
        -Wno-attributes
        -Wnull-dereference
        -Wno-unused-command-line-argument
        )