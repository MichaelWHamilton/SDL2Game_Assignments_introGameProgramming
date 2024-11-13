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
    SpriteComponent(GameObject& parent, std::string textureKey);
    SpriteComponent(GameObject& parent, std::string textureKey, int width, int height);

    void update() override;

    void draw() override;
private:
    SDL_Texture* texture;
    int width;               // Width of the sprite
    int height;
};

//#pragma once
//#include "Component.h"
//#include "GameObject.h"
//#include <SDL2/SDL.h>
//#include <string>
//#include "Textures.h"
//
//class SpriteComponent : public Component {
//public:
//    SpriteComponent(GameObject& parent, std::string textureKey);
//    SpriteComponent(GameObject& parent, std::string textureKey, int width, int height);
//
//    void update() override;
//
//    void draw() override;
//
//    void setAnimationRow(int row);
//
//    void setAnimationSpeed(int speed);
//
//private:
//    SDL_Texture* texture; 
//    int width;  
//    int height;
//    int currentFrame; 
//    int totalFrames;
//    int currentRow;
//    int animationSpeed;       
//    int frameCounter;         
//};
