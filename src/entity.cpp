#include "entity.h"

auto entity::parent() const -> std::shared_ptr<entity> { return parent_; }

auto entity::transform() const -> const ::transform& { return transform_; }

auto entity::transform() -> ::transform& { return transform_; }

void entity::update_matrices() {
    if(parent_ != nullptr) {
        transform_.set_parent_matrix(parent_->transform().world_matrix());
        for(auto& child : childrens_)
            child->update_matrices();
    }
}

void entity::draw() {
    for(auto& child : childrens_)
        child->draw();
}
