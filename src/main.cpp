#include "engine.h"
#include "gl_render_factory.h"
#include "material.h"
#include "transform.h"
#include "point_light.h"
#include "camera.h"
#include "cube_mesh.h"
#include "model.h"
#include <cmath>

#include <GLFW/glfw3.h>

class demoapp : public engine {
 public:
    explicit demoapp() : engine(factory_) {}

 protected:
    void init() override {
        auto material = std::make_shared<::material>();
        material->load_material("../res/standard.material", factory_);
        mesh_ = std::make_unique<cube_mesh>(factory_, material);

        model_ = std::make_unique<model>(factory_, "../res/guitar/backpack.obj");
        model_->set_uniform("material.diffuse", 0);
        model_->set_uniform("material.specular", 2);
        model_->set_uniform("material.shininess", 32.0F);

        camera_.set_position({0.0F, 0.1F, 6.0F});
        light_.set_position({1.2F, 1.0F, 2.0F});
        light_.set_ambient({0.5F, 0.5F, 0.5F});
    }

    template<typename T>
    void set_shader_params(T* m) {
        m->set_uniform("viewPos", camera_.position());
        m->set_uniform("projection", camera_.projection_matrix());
        m->set_uniform("view", camera_.view_matrix());
        m->set_uniform("model", model_transform_.matrix());
        m->set_uniform("point_lights[0].position", light_.position());
        m->set_uniform("point_lights[0].ambient", light_.ambient());
        m->set_uniform("point_lights[0].diffuse", light_.diffuse());
        m->set_uniform("point_lights[0].specular", light_.specular());
        m->set_uniform("point_lights[0].constant", light_.attenuation_constant());
        m->set_uniform("point_lights[0].linear", light_.attenuation_linear());
        m->set_uniform("point_lights[0].quadratic", light_.attenuation_quadratic());
        m->set_uniform("num_point_lights", 1);
    }

    void render_cube () {
        auto m = mesh_->material();
        m->select();
        set_shader_params(m.get());
        mesh_->draw();
    }

    void render_model() {
        set_shader_params(model_.get());
        model_->draw();
    }

    void render() override {
        /* render_cube(); */
        render_model();
    }

    void update(float elapsed) override {
        move_object(elapsed);
        move_camera(elapsed);
    }

 private:
    gl_render_factory factory_;
    float delta_{0};
    transform model_transform_;
    camera camera_;
    point_light light_;
    std::unique_ptr<mesh> mesh_;
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
