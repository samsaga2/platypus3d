#include <utility>
#include <chrono>
#include "render_factory.h"

class GLFWwindow;

class engine {
public:
    explicit engine(render_factory& factory);
    virtual ~engine();

    void create();
    void run();
    void main_loop();
    void quit();

protected:
    [[nodiscard]] auto factory() const -> render_factory& {
        return factory_;
    }

    virtual void init() {}
    virtual void render() {}
    virtual void update([[maybe_unused]] float elapsed) {}

private:
    render_factory& factory_;
    GLFWwindow *window_{nullptr};
    std::chrono::high_resolution_clock::time_point curr_time_;

    [[nodiscard]] auto get_window_size() const -> std::pair<int, int>;

    static void framebuffer_size_callback(GLFWwindow *window, int width,
                                          int height);
    void destroy();
};
