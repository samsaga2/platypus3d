#include <GLFW/glfw3.h>
#include <utility>

class PlatypusEngine {
public:
    virtual ~PlatypusEngine();

    void create();
    void run();
    void main_loop();
    void quit();

protected:
    virtual void init() {}
    virtual void render() {}
    virtual void update([[maybe_unused]] float elapsed) {}

private:
    GLFWwindow *window_{nullptr};
    float curr_time_;

    [[nodiscard]] auto get_window_size() const -> std::pair<int, int>;

    static void framebuffer_size_callback(GLFWwindow *window, int width,
                                          int height);
    void destroy();
};
