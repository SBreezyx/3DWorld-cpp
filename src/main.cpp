#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

#include <sys/window.hpp>
#include <gl/shader.hpp>
#include <gl/program.hpp>
#include <gl/vao.hpp>

auto render(std::chrono::seconds delta) -> void;

auto main() -> int
{
    auto window = sys::window(1280, 720, "Da Window");

    auto vert_src = std::ifstream("assets/shaders/vert.glsl");
    auto vert = gl::vertex_shader(std::string(std::istreambuf_iterator<char>(vert_src), {}));

    if (!vert.compile()) {
        throw std::runtime_error(vert.get_log());
    }

    auto frag_src = std::ifstream("assets/shaders/frag.glsl");
    auto frag = gl::fragment_shader(std::string(std::istreambuf_iterator<char>(frag_src), {}));

    if (!frag.compile()) {
        throw std::runtime_error(frag.get_log());
    }

    auto render_prog = gl::program(vert, frag);
    if (!(render_prog.link() && render_prog.is_valid())) {
        std::cout << "the log" << render_prog.get_log();
        throw std::runtime_error("");
    }
    render_prog.use();

    auto vao = gl::vao();
    vao.bind();

    auto time_then = std::chrono::steady_clock::now();
    while (!window.closed()) {
        auto time_now = std::chrono::steady_clock::now();
        render(std::chrono::duration_cast<std::chrono::seconds>(time_now - time_then));
        window.refresh();
    }
}

auto render(std::chrono::seconds delta) -> void
{
    const float color[] = {
            static_cast<float>(std::sin(delta.count())) * 0.5f + 0.5f,
            static_cast<float>(std::cos(delta.count())) * 0.5f + 0.5f,
            static_cast<float>(std::sin(delta.count())) * 0.5f + 0.5f,
            1.0f
    };
    glClearBufferfv(GL_COLOR, 0, color);

    glDrawArrays(GL_POINTS, 0, 1);
}