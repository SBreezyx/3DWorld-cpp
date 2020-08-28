//
// Created by Simon on 0027, 27 August 2020.
//

#ifndef INC_3DWORLD_C_WINDOW_HPP
#define INC_3DWORLD_C_WINDOW_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sys {
    class window {
    public:
        window(std::size_t w, std::size_t h, const std::string &title);

        window(const window &) = delete;
        window(window&&) = default;

        auto operator=(const window&) -> window& = delete;
        auto operator=(window&&) -> window& = default;

        ~window() noexcept;

        [[nodiscard]] auto closed() const noexcept -> bool;

        auto refresh() -> void;

    private:
        GLFWwindow *win_;
    };

}


#endif //INC_3DWORLD_C_WINDOW_HPP
