#include "engine.h"
#include <iostream>

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

    curr_time_ = glfwGetTime();
    init();
}

void engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void engine::main_loop() {
    auto time = glfwGetTime();
    auto elapsed = time - curr_time_;
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
