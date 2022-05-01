#pragma once

class texture {
 public:
    virtual ~texture() = default;

    virtual void select(unsigned int slot_index) = 0;
};
