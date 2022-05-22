#include "model.h"

model::model(std::vector<mesh> meshes) : meshes_(std::move(meshes)) {}

void model::draw() {
    for(auto& mesh : meshes_) {
        mesh.material()->select();
        mesh.draw();
    }
}
