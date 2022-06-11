#include "vertex_format.h"
#include <stdexcept>

void vertex_format::add_element(vertex_element e) {
    elements_.emplace_back(e);
}

auto vertex_format::length() const -> size_t {
    return elements_.size();
}

auto vertex_format::element_size(size_t index) const -> size_t {
    switch(elements_.at(index)) {
    case vertex_element::position:
        return 3;
    case vertex_element::texcoord:
        return 2;
    case vertex_element::colors:
        return 3;
    case vertex_element::normals:
        return 3;
    }
    throw std::runtime_error("unknown vertex format element");
}

auto vertex_format::element_type(size_t index) const -> vertex_element {
    return elements_.at(index);
}

auto vertex_format::total_size() const -> size_t {
    auto total_size = 0U;
    for(auto i = 0U; i < length(); i++)
        total_size += element_size(i);
    return total_size;
}
