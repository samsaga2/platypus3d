#include <GLFW/glfw3.h>
#include <utility>

class PlatypusEngine {
 public:
    ~PlatypusEngine();

    void init();
    void run();
    void main_loop();
    void quit();

 private:
    GLFWwindow *window_{nullptr};
    float red_{0.0f};
    float curr_time_;

    [[nodiscard]] auto get_window_size() const -> std::pair<int, int>;

    void render();
    void update(float elapsed);
    void destroy();
};
