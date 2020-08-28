//
// Created by Simon on 0028, 28 August 2020.
//

#ifndef INC_3DWORLD_C_VAO_HPP
#define INC_3DWORLD_C_VAO_HPP

#include <glad/glad.h>

namespace gl {
    class vao {
    public:
        vao();

        auto bind() const -> void;

    private:
        GLuint vao_;
    };
}


#endif //INC_3DWORLD_C_VAO_HPP
