#pragma once

#include <vector>
#include "mesh.h"
#include "material.h"

class model {
public:
    explicit model(std::vector<mesh> meshes);

    template<typename T>
    void set_uniform(const char* name, const T& value) {
        for(auto& mesh : meshes_) {
            mesh.material()->select();
            mesh.material()->set_uniform(name, value);
        }
    }

    void draw();

private:
    std::vector<mesh> meshes_;
};
