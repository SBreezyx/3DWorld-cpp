//
// Created by Simon on 0027, 27 August 2020.
//

#include <cassert>
#include <stdexcept>

#include <fmt/format.h>
#include <gsl/gsl-lite.hpp>

#include <sys/window.hpp>

namespace {
    struct glfw_init {
        glfw_init() noexcept
        {
            assert(glfwInit());
        }

        ~glfw_init()
        {
            glfwTerminate();
        }

    } init;
}

namespace sys {
    window::window(std::size_t w, std::size_t h, const std::string &title)
            : win_{
            glfwCreateWindow(gsl::narrow_cast<int>(w), gsl::narrow_cast<int>(h), title.data(), nullptr, nullptr) }
    {
        if (!win_) {
            throw std::runtime_error(fmt::format("Could not initialise window {}.", title));
        }

        glfwMakeContextCurrent(win_);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error(fmt::format("Failed to initialize OpenGL context for {title}.", title));
        }

        fmt::print("Using OpenGL {}.{}", GLVersion.major, GLVersion.minor);
    }

    window::~window() noexcept
    {
        glfwDestroyWindow(win_);
    }

    auto window::closed() const noexcept -> bool
    {
        return glfwWindowShouldClose(win_);
    }

    auto window::render() -> void
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win_);

        glfwPollEvents();
    }
}
