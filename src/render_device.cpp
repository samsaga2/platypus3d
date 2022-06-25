#include "render_device.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>

void render_device::create_window(int width, int height) {
    if (!glfwInit()) {
        std::cerr << "Error initializing glfw" << std::endl;
        quit();
        return;
    }

    window_ = glfwCreateWindow(width, height, "Platypus", nullptr, nullptr);
    if (!window_) {
        std::cerr << "Error creating window" << std::endl;
        quit();
        return;
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_,
                                   &render_device::framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
}

render_device::~render_device() {
    if (window_ != nullptr)
        glfwDestroyWindow(window_);
    glfwTerminate();
}

void render_device::framebuffer_size_callback(GLFWwindow* window, int width,
                                              int height) {
    glViewport(0, 0, width, height);
}

void render_device::run_loop(std::function<void(float)> update_fn) {
    auto prev_time = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window_)) {
        // calc elapsed time
        auto time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                           time - prev_time)
                           .count() /
                       1000.0f;
        prev_time = time;

        // escape key quit
        if (glfwGetKey(window_, GLFW_KEY_ESCAPE))
            quit();

        // update
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        update_fn(elapsed);

        // update glfw
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void render_device::quit() { glfwSetWindowShouldClose(window_, GL_TRUE); }

auto render_device::is_key_down(int key) -> bool {
    return glfwGetKey(window_, key);
}
