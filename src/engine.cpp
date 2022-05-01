#include "engine.h"

engine::engine(render_factory& factory) : factory_(factory) {}

void engine::create() {
    device_ = factory_.create_device();
    device_->create_window(800, 600);
    init();
}

void engine::quit() {
    device_->quit();
}

void engine::run() {
    device_->run_loop([&](float elapsed) {
            update(elapsed);
            render();
        });
}
