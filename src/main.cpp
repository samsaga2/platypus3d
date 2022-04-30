#include "engine.h"
#include "material.h"
#include "mesh.h"
#include "util.h"
#include "transform.h"
#include <cmath>
#include <iostream>

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
        delete mesh_;
        delete material_;
    }

 protected:
    void init() override {
        material_ = new material("../res/simple.material");
        mesh_ = new mesh(vertices, indices);
    }

    void render() override {
        // clear background
        glClearColor((std::sin(bg_red_) + 1.0) / 2.0,
                     (std::sin(bg_green_) + 1.0) / 2.0,
                     (std::sin(bg_blue_) + 1.0) / 2.0,
                     1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // move
        auto pos = glm::vec3{sinf(glfwGetTime())*0.5, 0, 0};
        mesh_transform_.set_position(pos);

        auto ori = glm::angleAxis(sinf(glfwGetTime()), glm::vec3{0, 0, 1});
        mesh_transform_.set_orientation(ori);

        // draw mesh
        auto m = mesh_transform_.model_matrix();
        material_->shader()->set_uniform("transform", m);
        material_->use();
        mesh_->draw();
    }

    void update(float elapsed) override {
        bg_red_ += elapsed * 8;
        bg_green_ += elapsed * 6;
        bg_blue_ += elapsed * 4;
    }

 private:
    float bg_red_{0.0f};
    float bg_green_{0.0f};
    float bg_blue_{0.0f};
    material* material_;
    mesh* mesh_;
    transform mesh_transform_;
};

int main() {
    auto test = Test{};
    test.create();
    test.run();
    return 0;
}
