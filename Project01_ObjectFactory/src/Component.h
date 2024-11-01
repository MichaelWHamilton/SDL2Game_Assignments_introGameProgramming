#pragma once
#include <iostream>
class Component {
public:
    virtual ~Component() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
};