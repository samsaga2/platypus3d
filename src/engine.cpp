#include "engine.h"
#include <iostream>
#include <GLFW/glfw3.h>

engine::engine(render_factory& factory) : factory_(factory) {}

engine::~engine() { destroy(); }

void engine::create() {
    if (!glfwInit()) {
        std::cerr << "Error initializing glfw" << std::endl;
        quit();
        return;
    }

    auto [width, height] = get_window_size();
    window_ = glfwCreateWindow(width, height, "Platypus", nullptr, nullptr);
    if (!window_) {
        std::cerr << "Error creating window" << std::endl;
        quit();
        return;
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, &engine::framebuffer_size_callback);

    curr_time_ = std::chrono::high_resolution_clock::now();
    init();
}

void engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void engine::main_loop() {
    auto time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time-curr_time_).count() / 1000.0f;
    curr_time_ = time;

    if (glfwGetKey(window_, GLFW_KEY_ESCAPE))
        quit();

    glClear(GL_COLOR_BUFFER_BIT);
    update(elapsed);
    render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void engine::destroy() {
    if (window_ != nullptr)
        glfwDestroyWindow(window_);
    glfwTerminate();
}

auto engine::get_window_size() const -> std::pair<int, int> {
    return {800, 600};
}

void engine::run() {
    while (!glfwWindowShouldClose(window_))
        main_loop();
}

void engine::quit() { glfwSetWindowShouldClose(window_, GL_TRUE); }
