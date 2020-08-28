//
// Created by Simon on 0028, 28 August 2020.
//

#include <gl/program.hpp>

namespace gl {

    program::program() noexcept: prog_{ glCreateProgram() }
    { }

    program::program(program &&other) noexcept: prog_{ std::exchange(other.prog_, 0) }
    { }

    auto program::operator=(program &&other) noexcept -> program &
    {
        if (this != &other) {
            program(std::move(other)).swap(*this);
        }
        return *this;
    }

    program::~program() noexcept
    {
        glDeleteProgram(prog_);
    }

    // Semantically, linking is mutating, just not to *this
    // NOLINTNEXTLINE
    auto program::link() -> bool
    {
        glLinkProgram(prog_);
        auto answer = 0;
        glGetProgramiv(prog_, GL_LINK_STATUS, &answer);
        return static_cast<bool>(answer);
    }

    auto program::is_valid() const noexcept -> bool
    {
        glValidateProgram(prog_);
        auto answer = 0;
        glGetProgramiv(prog_, GL_VALIDATE_STATUS, &answer);
        return static_cast<bool>(answer);
    }

    auto program::get_log() const -> std::string
    {
        auto len = 0;
        glGetShaderiv(prog_, GL_INFO_LOG_LENGTH, &len);
        auto log = std::string(len, 'a');
        glGetShaderInfoLog(prog_, len, std::nullptr_t{ }, log.data());
        return log;
    }

    auto program::swap(program &other) -> program &
    {
        std::swap(other.prog_, prog_);
        return *this;
    }

    auto program::use() const -> void
    {
        glUseProgram(prog_);
    }
}
