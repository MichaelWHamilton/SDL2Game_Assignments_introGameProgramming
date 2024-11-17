#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "BodyComponent.h"


class CharacterControllerComponent : public Component {
public:
    CharacterControllerComponent(GameObject& owner, float speed);

    void update() override;

    void draw() override;
private:
    float m_speed;

    void move(float dx, float dy);
};