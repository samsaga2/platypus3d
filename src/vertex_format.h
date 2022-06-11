#pragma once

#include <vector>
#include <cstddef>

enum class vertex_element {
    position,
    texcoord,
    colors,
    normals
};

class vertex_format {
 public:
    void add_element(vertex_element e);
    
    [[nodiscard]] auto length() const -> size_t;
    [[nodiscard]] auto element_size(size_t index) const -> size_t;
    [[nodiscard]] auto element_type(size_t index) const -> vertex_element;
    [[nodiscard]] auto total_size() const -> size_t;

 private:
    std::vector<vertex_element> elements_;
};
