#include "mesh.h"
#include "vertex_buffer.h"
#include "material.h"

mesh::mesh(std::shared_ptr<::vertex_buffer> vertex_buffer,
           std::shared_ptr<::material> material)
: vertex_buffer_(std::move(vertex_buffer)), material_(std::move(material)) {}

void mesh::draw() {
    material_->select();
    vertex_buffer_->draw();
}
