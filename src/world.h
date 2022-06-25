#pragma once

#include "camera.h"
#include "point_light.h"
#include "uniform_block.h"
#include <memory>

class entity;

class world {
  public:
    explicit world();

    [[nodiscard]] auto scene_root() -> std::shared_ptr<entity>;
    [[nodiscard]] auto camera() -> camera&;
    [[nodiscard]] auto light() -> point_light&;
    [[nodiscard]] auto matrices_block() -> std::shared_ptr<uniform_block>;
    [[nodiscard]] auto lights_block() -> std::shared_ptr<uniform_block>;

    void update_uniform_block();
    void draw();

  private:
    std::shared_ptr<entity> scene_root_;
    ::camera camera_;
    point_light light_;
    std::shared_ptr<uniform_block> matrices_block_;
    std::shared_ptr<uniform_block> lights_block_;
};
