#pragma once
#include <iostream>
#include "Component.h"
#include "Textures.h"
class SpriteComponent : public Component {
public:
    void update() override { std::cout << "Updating SpriteComponent\n"; }
    void draw() override { std::cout << "Drawing SpriteComponent\n"; }
};