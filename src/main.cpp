#include "engine.h"
#include "shader.h"
#include "model.h"
#include <cmath>

const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

static const auto vertices = std::vector<float>{
    0.5f,  0.5f,  0.0f, // top right
    0.5f,  -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f  // top left
};

static const auto indices = std::vector<unsigned int>{
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
};

class Test : public PlatypusEngine {
 public:
    ~Test() {
        delete model_;
        delete shader_;
    }

 protected:
    void init() override {
        shader_ = new shader(vertex_shader_source, fragment_shader_source);
        model_ = new model(vertices, indices);
    }

    void render() override {
        glClearColor((std::sin(bg_red_) + 1.0) / 2.0,
                     (std::sin(bg_green_) + 1.0) / 2.0,
                     (std::sin(bg_blue_) + 1.0) / 2.0,
                     1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader_->use();
        model_->draw();
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
    shader* shader_;
    model* model_;
};

int main() {
    auto test = Test{};
    test.create();
    test.run();
    return 0;
}
