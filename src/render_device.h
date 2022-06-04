#pragma once

#include <functional>

class GLFWwindow;

class render_device {
 public:
    ~render_device();

    [[nodiscard]] auto is_key_down(int key) -> bool;

    void create_window(int width, int heigh);
    void run_loop(std::function<void(float)> update_fn);
    void quit();

 private:
    GLFWwindow *window_{nullptr};

    static void framebuffer_size_callback(GLFWwindow *window, int width,
                                          int height);
};
