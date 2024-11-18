#pragma once
#include "Engine.h"
#include "Component.h"
#include "BodyComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "Textures.h"

#include "GameObject.h"
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
