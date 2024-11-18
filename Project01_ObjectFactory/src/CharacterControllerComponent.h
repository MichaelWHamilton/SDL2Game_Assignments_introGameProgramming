#pragma once
#include <iostream>
#include <memory>
#include "SDL2/SDL.h"
#include "Component.h"

class GameObject;
class CharacterControllerComponent : public Component {
public:
    CharacterControllerComponent(GameObject& owner, float speed);

    void update() override;

    void draw() override;
private:
    float m_speed;

    void move(float dx, float dy);
};