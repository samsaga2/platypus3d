#include <utility>
#include <chrono>
#include "render_device.h"

class GLFWwindow;

class engine {
public:
    void create();
    void run();
    void quit();

protected:
    virtual void init() {}
    virtual void render() {}
    virtual void update([[maybe_unused]] float elapsed) {}
    [[nodiscard]] auto is_key_down(int key) -> bool;
    
private:
    render_device device_;
};
