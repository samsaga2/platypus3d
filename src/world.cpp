#include "world.h"
#include "entity.h"

world::world() {
    scene_root_ = std::make_shared<entity>();

    // default scene
    camera_.set_position({0.0F, 0.1F, 6.0F});
    light_.set_position({1.2F, 1.0F, 2.0F});
    light_.set_ambient({0.5F, 0.5F, 0.5F});

    // uniform block
    matrices_block_ = std::make_unique<uniform_block>(0, 144);
    lights_block_ = std::make_unique<uniform_block>(1, 88);
}

auto world::scene_root() -> std::shared_ptr<entity> { return scene_root_; }

auto world::matrices_block() -> std::shared_ptr<uniform_block> {
    return matrices_block_;
}

auto world::lights_block() -> std::shared_ptr<uniform_block> {
    return lights_block_;
}

void world::draw() {
    update_uniform_block();
    scene_root_->update_matrices();
    scene_root_->draw();
}

auto world::camera() -> ::camera& { return camera_; }

void world::update_uniform_block() {
    matrices_block_->set_data(16, camera_.projection_matrix());
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
