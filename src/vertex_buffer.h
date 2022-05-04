#pragma once

#include <glm/glm.hpp>

class vertex_buffer {
public:
    virtual ~vertex_buffer() = default;
    
    virtual void draw() = 0;
};
