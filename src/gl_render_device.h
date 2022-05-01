#pragma once

#include "render_device.h"

class GLFWwindow;

class gl_render_device : public render_device {
 public:
    ~gl_render_device();

    void create_window(int width, int heigh) override;
    void run_loop(std::function<void(float)> update_fn) override;
    void quit() override;

 private:
    GLFWwindow *window_{nullptr};

    static void framebuffer_size_callback(GLFWwindow *window, int width,
                                          int height);
};
