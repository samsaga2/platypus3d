#include "engine.h"
#include "gl_material.h"
#include "gl_vertex_buffer.h"
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

class Test : public PlatypusEngine {
 public:
    ~Test() {
        delete vertex_buffer_;
        delete material_;
    }

 protected:
    void init() override {
        material_ = new gl_material("../res/simple.material");
        vertex_buffer_ = new gl_vertex_buffer(vertices, indices);
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
    material* material_;
    vertex_buffer* vertex_buffer_;
    transform mesh_transform_;
};

int main() {
    auto test = Test{};
    test.create();
    test.run();
    return 0;
}
