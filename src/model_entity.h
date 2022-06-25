#pragma once

#include "entity.h"

class model;

class model_entity : public entity {
  public:
    explicit model_entity(world& w, const std::shared_ptr<::model>& model);

    [[nodiscard]] auto model() const -> std::shared_ptr<::model>;

    void draw();

  private:
    std::shared_ptr<::model> model_;
};
