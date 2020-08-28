//
// Created by Simon on 0028, 28 August 2020.
//

#ifndef INC_3DWORLD_C_SHADER_HPP
#define INC_3DWORLD_C_SHADER_HPP

#include <string>
#include <utility>
#include <istream>

#include <gsl/gsl-lite.hpp>

#include <glad/glad.h>

namespace gl {
    enum class SHADER : unsigned {
        COMPUTE_SHADER = GL_COMPUTE_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
        GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
        VERTEX_SHADER = GL_VERTEX_SHADER,
    };

    template<SHADER T>
    class shader {
    public:

        explicit shader(const std::string &src) : shader_{ glCreateShader(static_cast<GLenum>(T)) }
        {
            auto src_str = src.data();
            auto src_sz = gsl::narrow_cast<GLint>(src.length());
            glShaderSource(shader_, 1, &src_str, &src_sz);
        }

        shader(const shader &) = delete;

        shader(shader &&other) noexcept: shader_{ std::exchange(other.shader_, 0) }
        { }

        auto operator=(const shader &) -> shader & = delete;

        auto operator=(shader &&other) noexcept -> shader &
        {
            if (this != &other) {
                shader(std::move(other)).swap(*this);
            }
            return *this;
        }

        ~shader() noexcept
        {
            glDeleteShader(shader_);
        }

        explicit operator GLuint() const noexcept {
            return shader_;
        }

        auto compile() -> bool
        {
            glCompileShader(shader_);
            auto answer = 0;
            glGetShaderiv(shader_, GL_COMPILE_STATUS, &answer);
            return static_cast<bool>(answer);
        }

        [[nodiscard]] auto get_log() const noexcept -> std::string
        {
            auto len = 0;
            glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &len);
            auto log = std::string(len, '\0');
            glGetShaderInfoLog(shader_, len, std::nullptr_t{ }, log.data());
            return log;
        }

        [[nodiscard]] auto get_shader_source() const noexcept -> std::string
        {
            auto len = 0;
            glGetShaderiv(shader_, GL_SHADER_SOURCE_LENGTH, &len);
            auto src = std::string(len, '\0');
            glGetShaderInfoLog(shader_, len, std::nullptr_t{ }, src.data());
            return src;
        }

        auto swap(shader &other) -> shader&
        {
            std::swap(other.shader_, shader_);
            return *this;
        }

    private:
        GLuint shader_;
    };

    using compute_shader = shader<SHADER::COMPUTE_SHADER>;
    using fragment_shader = shader<SHADER::FRAGMENT_SHADER>;
    using geometry_shader = shader<SHADER::GEOMETRY_SHADER>;
    using tess_control_shader = shader<SHADER::TESS_CONTROL_SHADER>;
    using tess_evaluation_shader = shader<SHADER::TESS_EVALUATION_SHADER>;
    using vertex_shader = shader<SHADER::VERTEX_SHADER>;
}


#endif //INC_3DWORLD_C_SHADER_HPP
