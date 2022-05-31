#include "engine.h"
#include "gl_render_factory.h"
#include "gl_uniform_block.h"
#include "transform.h"
#include "point_light.h"
#include "camera.h"
#include "model_loader.h"
#include <cmath>
#include <cstddef>

#include <GLFW/glfw3.h>

class demoapp : public engine {
    struct matrices_block_data {
        glm::mat4 projection;
        glm::mat4 view;
    } __attribute__((aligned(16)));

 public:
    explicit demoapp() : engine(factory_) {}

 protected:
    void init() override {
        auto model_loader = ::model_loader(factory_);
        model_ = std::make_unique<model>(model_loader.load_model("../res/guitar/backpack.obj"));
        model_->set_uniform("material.diffuse", 0);
        model_->set_uniform("material.specular", 2);
        model_->set_uniform("material.shininess", 32.0F);

        camera_.set_position({0.0F, 0.1F, 6.0F});
        light_.set_position({1.2F, 1.0F, 2.0F});
        light_.set_ambient({0.5F, 0.5F, 0.5F});

        matrices_block_ = std::make_unique<gl_uniform_block>(0, sizeof(matrices_block_data));
        matrices_block_->set_data(offsetof(struct matrices_block_data, projection), camera_.projection_matrix());
        model_->set_uniform_block("Matrices", matrices_block_->binding_point());
    }

    void update_model() {
        matrices_block_->set_data(offsetof(struct matrices_block_data, view),
                                  camera_.view_matrix());
        model_->set_uniform("viewPos", camera_.position());
        model_->set_uniform("model", model_transform_.matrix());
        model_->set_uniform("num_point_lights", 1);
        model_->set_uniform("point_lights[0].position", light_.position());
        model_->set_uniform("point_lights[0].ambient", light_.ambient());
        model_->set_uniform("point_lights[0].diffuse", light_.diffuse());
        model_->set_uniform("point_lights[0].specular", light_.specular());
        model_->set_uniform("point_lights[0].constant", light_.attenuation_constant());
        model_->set_uniform("point_lights[0].linear", light_.attenuation_linear());
        model_->set_uniform("point_lights[0].quadratic", light_.attenuation_quadratic());
    }

    void render_model() {
        update_model();
        model_->draw();
    }

    void render() override {
        render_model();
    }

    void update(float elapsed) override {
        move_object(elapsed);
        move_camera(elapsed);
    }

 private:
    gl_render_factory factory_;
    std::unique_ptr<gl_uniform_block> matrices_block_;
    std::unique_ptr<gl_uniform_block> lights_block_;
    float delta_{0};
    transform model_transform_;
    camera camera_;
    point_light light_;
    std::unique_ptr<model> model_;

    void move_object(float elapsed) {
        delta_ += elapsed;

        auto ori = glm::angleAxis(sinf(delta_)*0.5f, glm::vec3{0, 2.0, 1});
        model_transform_.set_orientation(ori);
    }

    void move_camera(float elapsed) {
        auto pos = camera_.position();
        if (is_key_down(GLFW_KEY_UP) || is_key_down(GLFW_KEY_W))
            pos += camera_.front() * elapsed;
        if (is_key_down(GLFW_KEY_DOWN) || is_key_down(GLFW_KEY_S))
            pos -= camera_.front() * elapsed;
        if (is_key_down(GLFW_KEY_A))
            pos -= camera_.right() * elapsed;
        if (is_key_down(GLFW_KEY_D))
            pos += camera_.right() * elapsed;
        if (is_key_down(GLFW_KEY_LEFT))
            camera_.set_yaw(camera_.yaw() - elapsed * 50.0f);
        if (is_key_down(GLFW_KEY_RIGHT))
            camera_.set_yaw(camera_.yaw() + elapsed * 50.0f);
        camera_.set_position(pos);
    }
};

int main() {
    auto app = demoapp{};
    app.create();
    app.run();
    return 0;
}
