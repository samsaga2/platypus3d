#pragma once

class shader {
public:
    virtual ~shader() = default;

    virtual void select() = 0;
};
