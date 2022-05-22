#pragma once

#include <vector>

struct vertex {
    float x;
    float y;
    float z;
    float u;
    float v;
    float r;
    float g;
    float b;
    float nx;
    float ny;
    float nz;
};

[[nodiscard]]
auto deindex_vertices(const std::vector<vertex>& vertices,
                      const std::vector<unsigned int>& indices)
    -> std::vector<vertex>;
