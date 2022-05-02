#include "engine.h"
#include "gl_render_factory.h"
#include "material.h"
#include "transform.h"
#include <cmath>

static const auto vertices = std::vector<float>{
    // vertex           // texcoords
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
};

static const auto indices = std::vector<unsigned int>{
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
};

class demoapp : public engine {
 public:
    explicit demoapp() : engine(factory_) {}

 protected:
    void init() override {
        vertex_buffer_ = factory_.create_vertex_buffer(vertices, indices);
        material_ = std::make_unique<material>("../res/simple.material", factory_);

        view_ = glm::mat4(1.0f);
        view_ = glm::translate(view_, glm::vec3(0.0f, 0.0f, -3.0f));

        projection_ = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    }

    void render() override {
        auto m = projection_ * view_ * model_.matrix();
        material_->select();
        vertex_buffer_->draw(m);
    }

    void update(float elapsed) override {
        delta_ += elapsed;

        auto pos = glm::vec3{cosf(delta_)*0.5f, 0, 0};
        model_.set_position(pos);

        auto ori = glm::angleAxis(sinf(delta_)*0.5f, glm::vec3{0, 0, 1});
        model_.set_orientation(ori);
    }

 private:
    gl_render_factory factory_;
    float delta_{0};
    std::unique_ptr<material> material_;
    std::shared_ptr<vertex_buffer> vertex_buffer_;
    transform model_;
    glm::mat4 view_;
    glm::mat4 projection_;
};

int main() {
    auto app = demoapp{};
    app.create();
    app.run();
    return 0;
}
