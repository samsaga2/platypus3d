#include "engine.h"
#include "gl_render_factory.h"
#include "material.h"
#include "transform.h"
#include "point_light.h"
#include "camera.h"
#include <cmath>

#include <GLFW/glfw3.h>

static const auto vertices = std::vector<float>{
    // vertex             // texcoords   // colors           // normals
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
  
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
  
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
  
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
  
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
  
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f
};

class demoapp : public engine {
 public:
    explicit demoapp() : engine(factory_) {}

 protected:
    void init() override {
        vertex_buffer_ = factory_.create_vertex_buffer(vertices);
        material_ = std::make_unique<material>("../res/standard.material", factory_);
        camera_.set_position({0.0f, 0.1f, 3.0f});
        light_.set_position({1.2f, 1.0f, 2.0f});
    }

    void render() override {
        // select material
        material_->select();
        material_->set_uniform("viewPos", camera_.position());
        material_->set_uniform("projection", camera_.projection_matrix());
        material_->set_uniform("view", camera_.view_matrix());
        material_->set_uniform("model", model_.matrix());

        material_->set_uniform("point_lights[0].position", light_.position());
        material_->set_uniform("point_lights[0].ambient", light_.ambient());
        material_->set_uniform("point_lights[0].diffuse", light_.diffuse());
        material_->set_uniform("point_lights[0].specular", light_.specular());
        material_->set_uniform("point_lights[0].constant", light_.attenuation_constant());
        material_->set_uniform("point_lights[0].linear", light_.attenuation_linear());
        material_->set_uniform("point_lights[0].quadratic", light_.attenuation_quadratic());
        material_->set_uniform("num_point_lights", 1);

        // render verex buffer
        vertex_buffer_->draw();
    }

    void update(float elapsed) override {
        move_object(elapsed);
        move_camera(elapsed);
    }

 private:
    gl_render_factory factory_;
    float delta_{0};
    std::unique_ptr<material> material_;
    std::shared_ptr<vertex_buffer> vertex_buffer_;
    transform model_;
    camera camera_;
    point_light light_;

    void move_object(float elapsed) {
        delta_ += elapsed;

        auto ori = glm::angleAxis(sinf(delta_)*0.5f, glm::vec3{0, 2.0, 1});
        model_.set_orientation(ori);
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
