#include "model.h"

model::model(std::vector<mesh> meshes) : meshes_(std::move(meshes)) {}

void model::draw() {
    for (auto& mesh : meshes_) {
        mesh.material()->select();
        mesh.draw();
    }
}

void model::set_uniform_block(const char* name, int block_index) {
    for (auto& mesh : meshes_) {
        mesh.material()->select();
        mesh.material()->set_uniform_block(name, block_index);
    }
}
