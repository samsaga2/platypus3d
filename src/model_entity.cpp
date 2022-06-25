#include "model_entity.h"
#include "model.h"
#include "world.h"

model_entity::model_entity(world& w, const std::shared_ptr<::model>& model)
    : model_(std::move(model)) {
    model_->set_uniform_block("Matrices", w.matrices_block()->binding_point());
    model_->set_uniform_block("Lights", w.lights_block()->binding_point());
}

auto model_entity::model() const -> std::shared_ptr<::model> { return model_; }

void model_entity::draw() {
    model_->set_uniform("model", transform().world_matrix());
    model_->draw();
    entity::draw();
}
