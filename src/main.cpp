#include <iostream>

#include <sys/window.hpp>

auto main() -> int {
    auto window = sys::window(1280, 720, "Da Window");

    while (!window.closed())
    {
        window.render();
    }
}
