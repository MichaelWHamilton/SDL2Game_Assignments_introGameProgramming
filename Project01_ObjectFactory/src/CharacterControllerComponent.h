#pragma once
#include <iostream>
#include <memory>
#include "SDL2/SDL.h"
#include "Component.h"
#include "box2d/box2d.h"
#include "box2d/b2_math.h"
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