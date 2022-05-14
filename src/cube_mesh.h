#pragma once

#include "mesh.h"

class render_factory;

class cube_mesh : public mesh {
 public:
    explicit cube_mesh(render_factory& factory,
                       std::shared_ptr<::material> material);
};
