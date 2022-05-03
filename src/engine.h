#include <utility>
#include <chrono>
#include "render_factory.h"
#include "render_device.h"

class GLFWwindow;

class engine {
public:
    explicit engine(render_factory& factory);

    void create();
    void run();
    void quit();

protected:
    [[nodiscard]] auto factory() const -> render_factory& {
        return factory_;
    }

    virtual void init() {}
    virtual void render() {}
    virtual void update([[maybe_unused]] float elapsed) {}
    [[nodiscard]] auto is_key_down(int key) -> bool;
    
private:
    render_factory& factory_;
    std::shared_ptr<render_device> device_;
};
