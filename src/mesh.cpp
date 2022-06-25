#include "mesh.h"
#include "material.h"
#include "vertex_buffer.h"

mesh::mesh(std::shared_ptr<::vertex_buffer> vertex_buffer,
           std::shared_ptr<::material> material)
    : vertex_buffer_(std::move(vertex_buffer)), material_(std::move(material)) {
}

void mesh::draw() { vertex_buffer_->draw(); }
