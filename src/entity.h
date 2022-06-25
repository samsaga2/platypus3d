#pragma once

#include "transform.h"
#include <list>
#include <memory>

class world;

class entity {
  public:
    [[nodiscard]] auto parent() const -> std::shared_ptr<entity>;
    [[nodiscard]] auto transform() const -> const transform&;
    [[nodiscard]] auto transform() -> ::transform&;

    template <typename T, typename... Args>
    static auto create_child(world& w, std::shared_ptr<entity> parent,
                             const Args&... args) -> std::shared_ptr<T> {
        auto entity = std::make_shared<T>(w, args...);
        if (parent != nullptr) {
            parent->childrens_.emplace_back(entity);
            entity->parent_ = parent;
        }
        return entity;
    }

    void update_matrices();
    virtual void draw();

  private:
    ::transform transform_;
    std::list<std::shared_ptr<entity>> childrens_;
    std::shared_ptr<entity> parent_;
};
