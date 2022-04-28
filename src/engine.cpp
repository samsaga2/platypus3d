#include "engine.h"
#include <iostream>

PlatypusEngine::~PlatypusEngine() { destroy(); }

void PlatypusEngine::create() {
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
    glfwSetFramebufferSizeCallback(window_, &PlatypusEngine::framebuffer_size_callback);

    curr_time_ = glfwGetTime();
    init();
}

void PlatypusEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void PlatypusEngine::main_loop() {
    auto time = glfwGetTime();
    auto elapsed = time - curr_time_;
    curr_time_ = time;

    if (glfwGetKey(window_, GLFW_KEY_ESCAPE))
        quit();

    update(elapsed);
    render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void PlatypusEngine::destroy() {
    if (window_ != nullptr)
        glfwDestroyWindow(window_);
    glfwTerminate();
}

auto PlatypusEngine::get_window_size() const -> std::pair<int, int> {
    return {800, 600};
}

void PlatypusEngine::run() {
    while (!glfwWindowShouldClose(window_))
        main_loop();
}

void PlatypusEngine::quit() { glfwSetWindowShouldClose(window_, GL_TRUE); }
