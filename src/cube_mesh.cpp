#include "cube_mesh.h"
#include "render_factory.h"

static const auto vertices = std::vector<vertex>{
    // vertex              // texcoords   // colors           // normals
    {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f},
    {0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f},
    {0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f},
    {0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f},
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f},
  
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f},
    {0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f},
    {0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f},
    {0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f},
    {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f},
  
    {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f},
    {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f},
    {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f},
  
    {0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f},
    {0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f},
    {0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f},
    {0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f},
    {0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f},
    {0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f},
  
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f},
    {0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f},
    {0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f},
    {0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f},
  
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f},
    {0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f},
    {0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f},
    {0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f},
    {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f},
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f},
};

cube_mesh::cube_mesh(render_factory& factory,
                     std::shared_ptr<::material> material)
: mesh(factory.create_vertex_buffer(vertices), material)  {
}