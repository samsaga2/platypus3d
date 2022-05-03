#pragma once

#include <functional>

class render_device {
 public:
    virtual ~render_device() = default;

    virtual void create_window(int width, int height) = 0;
    virtual void run_loop(std::function<void(float)> update_fn) = 0;
    virtual void quit() = 0;

    [[nodiscard]] virtual auto is_key_down(int key) -> bool = 0;
};
