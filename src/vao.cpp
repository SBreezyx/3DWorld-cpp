//
// Created by Simon on 0028, 28 August 2020.
//

#include <gl/vao.hpp>

namespace gl {

    vao::vao() : vao_{}
    {
        glCreateVertexArrays(1, &vao_);
    }

    auto vao::bind() const -> void
    {
        glBindVertexArray(vao_);
    }
}