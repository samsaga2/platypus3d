#include "camera.h"
#include "engine.h"
#include "model_loader.h"
#include "point_light.h"
#include "transform.h"
#include "uniform_block.h"
#include <cmath>
#include <cstddef>

#include <GLFW/glfw3.h>

class demoapp : public engine {
  protected:
    void init() override {
        create_model();
        setup_uniform_block();
        create_scene();
    }

    void render() override {
        update_uniform_block();
        update_model_shader();
        model_->draw();
    }

    void update(float elapsed) override {
        move_object(elapsed);
        move_camera(elapsed);
    }

  private:
    std::unique_ptr<uniform_block> matrices_block_;
    std::unique_ptr<uniform_block> lights_block_;
    float delta_{0};
    transform model_transform_;
    camera camera_;
    point_light light_;
    std::unique_ptr<model> model_;

    void create_model() {
        auto model_loader = ::model_loader();
        model_ = std::make_unique<model>(
            model_loader.load_model("../res/guitar/backpack.obj"));
        model_->set_uniform("material.diffuse", 0);
        model_->set_uniform("material.specular", 2);
        model_->set_uniform("material.shininess", 32.0F);
    }

    void create_scene() {
        camera_.set_position({0.0F, 0.1F, 6.0F});
        light_.set_position({1.2F, 1.0F, 2.0F});
        light_.set_ambient({0.5F, 0.5F, 0.5F});
    }

    void setup_uniform_block() {
        matrices_block_ = std::make_unique<uniform_block>(0, 144);
        matrices_block_->set_data(16, camera_.projection_matrix());
        model_->set_uniform_block("Matrices", matrices_block_->binding_point());

        lights_block_ = std::make_unique<uniform_block>(1, 88);
        model_->set_uniform_block("Lights", lights_block_->binding_point());
    }

    void update_uniform_block() {
        matrices_block_->set_data(0, camera_.position());
        matrices_block_->set_data(80, camera_.view_matrix());

        lights_block_->set_data(0, 1);
        lights_block_->set_data(16, light_.position());
        lights_block_->set_data(32, light_.ambient());
        lights_block_->set_data(48, light_.diffuse());
        lights_block_->set_data(64, light_.specular());
        lights_block_->set_data(76, light_.attenuation_constant());
        lights_block_->set_data(80, light_.attenuation_linear());
        lights_block_->set_data(84, light_.attenuation_quadratic());
    }

    void update_model_shader() {
        model_->set_uniform("model", model_transform_.matrix());
    }

    void move_object(float elapsed) {
        delta_ += elapsed;

        auto ori = glm::angleAxis(sinf(delta_) * 0.5f, glm::vec3{0, 2.0, 1});
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
