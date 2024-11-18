#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <memory>
#include "Component.h"

class GameObject;
class SpriteComponent : public Component {
public:
    SpriteComponent(GameObject& parent, std::string textureKey, std::string name);
    //SpriteComponent(GameObject& parent, std::string textureKey, int width, int height);

    void update() override;

    void draw() override;

    std::string getName();
    
private:
    SDL_Texture* m_texture;
    std::string m_name;

};
