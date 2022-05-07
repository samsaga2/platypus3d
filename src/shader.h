#pragma once

#include <glm/glm.hpp>

class shader {
public:
    virtual ~shader() = default;

    virtual void select() = 0;
    virtual void set_uniform(const char* name, const glm::vec3& value) = 0;
    virtual void set_uniform(const char* name, const glm::mat4& value) = 0;
    virtual void set_uniform(const char* name, float value) = 0;
};
