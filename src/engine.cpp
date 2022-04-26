#include "engine.h"
#include "canvas.h"
#include <iostream>

PlatypusEngine::~PlatypusEngine() { destroy(); }

void PlatypusEngine::init() {
  if (!glfwInit()) {
    std::cerr << "Error initializing glfw" << std::endl;
    exit(-1);
    return;
  }

  auto [width, height] = get_window_size();
  window_ = glfwCreateWindow(width, height, "Platypus", nullptr, nullptr);
  if (!window_) {
    std::cerr << "Error creating window" << std::endl;
    exit(-1);
    return;
  }

  glfwMakeContextCurrent(window_);
  curr_time_ = glfwGetTime();
}

void PlatypusEngine::main_loop() {
  auto time = glfwGetTime();
  auto elapsed = time - curr_time_;
  curr_time_ = time;

  if (glfwGetKey(window_, GLFW_KEY_ESCAPE))
    quit();

  render();
  update(elapsed);
}

void PlatypusEngine::destroy() {
  if (window_ != nullptr)
    glfwDestroyWindow(window_);
  glfwTerminate();
}

void PlatypusEngine::render() {
  glClearColor(red_, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void PlatypusEngine::update(float elapsed) {
  red_ = red_ + elapsed / 2.0f;
  if (red_ > 1.0f)
    red_ = 0.0f;
}

#ifdef __EMSCRIPTEN__
static void run_main_loop(void *arg) {
  static_cast<PlatypusEngine *>(arg)->main_loop();
}

auto PlatypusEngine::get_window_size() const -> std::pair<int, int> {
  auto width = canvas_get_width();
  auto height = canvas_get_height();
  return {width, height};
}

void PlatypusEngine::run() {
  emscripten_set_main_loop_arg(&run_main_loop, this, 0, true);
}

void PlatypusEngine::quit() { emscripten_cancel_main_loop(); }
#else
auto PlatypusEngine::get_window_size() const -> std::pair<int, int> {
  return {800, 600};
}

void PlatypusEngine::run() {
  while (!glfwWindowShouldClose(window_))
    main_loop();
}

void PlatypusEngine::quit() { glfwSetWindowShouldClose(window_, GL_TRUE); }
#endif
