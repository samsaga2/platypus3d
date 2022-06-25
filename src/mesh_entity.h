#pragma once

#include "entity.h"

class mesh;

class mesh_entity : public entity {
 public:
    explicit mesh_entity(const std::shared_ptr<mesh>& mesh)
        : mesh_(std::move(mesh)) {}

    [[nodiscard]] auto mesh() const { return mesh_; }

    void draw()  {
        mesh_->draw();
        entity::draw();
    }

 private:
    std::shared_ptr<mesh> mesh_;
};
