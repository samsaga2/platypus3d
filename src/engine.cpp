#include "engine.h"

void engine::create() {
    device_.create_window(800, 600);
    init();
}

void engine::quit() {
    device_.quit();
}

void engine::run() {
    device_.run_loop([&](float elapsed) {
            update(elapsed);
            render();
        });
}

auto engine::is_key_down(int key) -> bool {
    return device_.is_key_down(key);
}
