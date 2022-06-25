#include "engine.h"
#include "model_entity.h"
#include "model_loader.h"
#include "world.h"
#include <cmath>

#include <GLFW/glfw3.h>

class demoapp : public engine {
  protected:
    void init() override {
        world_ = std::make_unique<world>();
        create_model();
    }

    void render() override { world_->draw(); }

    void update(float elapsed) override {
        move_object(elapsed);
        move_camera(elapsed);
    }

  private:
    float delta_{0};
    std::unique_ptr<world> world_;
    std::shared_ptr<model_entity> model_entity_;

    void create_model() {
        auto model_loader = ::model_loader();
        auto model = std::make_shared<::model>(
            model_loader.load_model("../res/guitar/backpack.obj"));
        model->set_uniform("material.diffuse", 0);
        model->set_uniform("material.specular", 2);
        model->set_uniform("material.shininess", 32.0F);

        model_entity_ = entity::create_child<::model_entity>(
            *world_.get(), world_->scene_root(), model);
    }

    void move_object(float elapsed) {
        delta_ += elapsed;

        auto ori = glm::angleAxis(sinf(delta_) * 0.5f, glm::vec3{0, 2.0, 1});
        model_entity_->transform().set_orientation(ori);
    }

    void move_camera(float elapsed) {
        auto& c = world_->camera();
        auto pos = c.position();
        if (is_key_down(GLFW_KEY_UP) || is_key_down(GLFW_KEY_W))
            pos += c.front() * elapsed;
        if (is_key_down(GLFW_KEY_DOWN) || is_key_down(GLFW_KEY_S))
            pos -= c.front() * elapsed;
        if (is_key_down(GLFW_KEY_A))
            pos -= c.right() * elapsed;
        if (is_key_down(GLFW_KEY_D))
            pos += c.right() * elapsed;
        if (is_key_down(GLFW_KEY_LEFT))
            c.set_yaw(c.yaw() - elapsed * 50.0f);
        if (is_key_down(GLFW_KEY_RIGHT))
            c.set_yaw(c.yaw() + elapsed * 50.0f);
        c.set_position(pos);
    }
};

int main() {
    auto app = demoapp{};
    app.create();
    app.run();
    return 0;
}
