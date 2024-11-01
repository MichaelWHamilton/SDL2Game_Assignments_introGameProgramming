#pragma once
#include <iostream>
#include "Component.h"
class BodyComponent : public Component {
public:
    void update() override { std::cout << "Updating BodyComponent\n"; }
    void draw() override { std::cout << "Drawing BodyComponent\n"; }
};