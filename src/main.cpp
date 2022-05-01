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
 protected:
    using engine::engine;
    
    void init() override {
        vertex_buffer_ = factory().create_vertex_buffer(vertices, indices);
        material_ = std::make_unique<material>("../res/simple.material", factory());
    }

    void render() override {
        // move
        auto pos = glm::vec3{sinf(glfwGetTime())*0.5, 0, 0};
        mesh_transform_.set_position(pos);

        auto ori = glm::angleAxis(sinf(glfwGetTime()), glm::vec3{0, 0, 1});
        mesh_transform_.set_orientation(ori);

        // draw mesh
        mesh_transform_.select();
        material_->select();
        vertex_buffer_->draw();
    }

 private:
    std::unique_ptr<material> material_;
    std::shared_ptr<vertex_buffer> vertex_buffer_;
    transform mesh_transform_;
};

int main() {
    auto factory = gl_render_factory{};
    auto app = demoapp{factory};
    app.create();
    app.run();
    return 0;
}
