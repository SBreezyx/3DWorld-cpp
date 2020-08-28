//
// Created by Simon on 0028, 28 August 2020.
//

#ifndef INC_3DWORLD_C_PROGRAM_HPP
#define INC_3DWORLD_C_PROGRAM_HPP

#include <utility>
#include <string>

#include <glad/glad.h>

namespace gl {
    class program {
    public:
        program() noexcept;

        template <typename ...Shader>
        explicit program(Shader&& ...shaders) : program() {
            attach_shaders(std::forward<Shader>(shaders)...);
        }

        program(const program &) = delete;
        program(program &&other) noexcept;

        auto operator=(const program &) -> program& = delete;
        auto operator=(program &&other) noexcept -> program&;

        ~program() noexcept;

        template <typename Shader, typename ...Shaders>
        auto attach_shaders(Shader &&shader, Shaders&& ...shaders) -> void {
            glAttachShader(prog_, static_cast<GLuint>(shader));
            attach_shaders(shaders...);
        }

        template <typename Shader>
        auto attach_shaders(Shader &&shader) -> void {
            glAttachShader(prog_, static_cast<GLuint>(shader));
        }

        auto link() -> bool;

        [[nodiscard]] auto is_valid() const noexcept -> bool;

        [[nodiscard]] auto get_log() const -> std::string;

        [[nodiscard]] auto use() const -> void;

        auto swap(program &other) -> program&;

    private:
        GLuint prog_;
    };
}


#endif //INC_3DWORLD_C_PROGRAM_HPP
