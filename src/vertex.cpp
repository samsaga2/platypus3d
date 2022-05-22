#include "vertex.h"

auto deindex_vertices(const std::vector<vertex>& vertices,
                      const std::vector<unsigned int>& indices)
    -> std::vector<vertex> {
    auto vertices_deindexed = std::vector<vertex>{};
    for(auto i = 0U; i < indices.size(); i+= 3U) {
        auto& v1 = vertices[indices[i+0]];
        auto& v2 = vertices[indices[i+1]];
        auto& v3 = vertices[indices[i+2]];
        vertices_deindexed.emplace_back(v1);
        vertices_deindexed.emplace_back(v2);
        vertices_deindexed.emplace_back(v3);
    }
    return vertices_deindexed;
}
