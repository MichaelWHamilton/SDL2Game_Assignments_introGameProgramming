#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey)
    : Component(parent), texture(nullptr), width(64), height(64) {
    texture = Textures::get(textureKey);
    if (!texture) {
        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
    }
}
SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey, int width, int height)
    : Component(parent), texture(nullptr), width(width), height(height) {
    texture = Textures::get(textureKey);
    if (!texture) {
        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
    }
}

void SpriteComponent::update(){}

//void SpriteComponent::draw(){
//    //SDL_Renderer* renderer = getRenderer();
//    auto body = getParent().get<BodyComponent>();
//    if (body) {
//        SDL_Rect dst = { static_cast<int>(body->x()), static_cast<int>(body->y()), width, height };
//
//        SDL_RenderCopy(Engine::getRenderer(), texture, nullptr, &dst);
//    }
//}

void SpriteComponent::draw() {
    auto body = getParent().get<BodyComponent>();
    if (body) {
        // Define destination rectangle based on the position from the BodyComponent
        SDL_Rect dst = {static_cast<int>(body->x()), static_cast<int>(body->y()),width,height};

        // Transform the destination rectangle to account for the view (camera) position and scale
        SDL_Rect transformedDst = Engine::camera.transformRect(dst);

        // Render the texture using the transformed rectangle
        SDL_RenderCopy(Engine::getRenderer(), texture, nullptr, &transformedDst);
    }
}

SDL_Texture* texture;
int width;               // Width of the sprite
int height;


//#include "SpriteComponent.h"
//#include "Textures.h"
//#include "Engine.h"
//#include "BodyComponent.h"
//
//SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey)
//    : Component(parent), texture(nullptr), width(41), height(48), currentFrame(0), totalFrames(3), currentRow(0), animationSpeed(10), frameCounter(0) {
//    texture = Textures::get(textureKey);
//    if (!texture) {
//        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
//    }
//}
//
//SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey, int width, int height)
//    : Component(parent), texture(nullptr), width(width), height(height), currentFrame(0), totalFrames(3), currentRow(0), animationSpeed(10), frameCounter(0) {
//    texture = Textures::get(textureKey);
//    if (!texture) {
//        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
//    }
//}
//void SpriteComponent::update() {
//    frameCounter++;
//
//    if (frameCounter >= animationSpeed) {
//        frameCounter = 0;
//        // Update the current frame
//        currentFrame++;
//        if (currentFrame >= totalFrames) {
//            currentFrame = 0;  // Loop the animation
//        }
//    }
//    int origSpeed = 0;
//    if (Input::isKeyDown(SDLK_w))
//    {
//        //animationSpeed = origSpeed;
//        setAnimationRow(2);
//    }
//    if (Input::isKeyDown(SDLK_s))
//    {
//        //animationSpeed = origSpeed;
//        setAnimationRow(0);
//    }
//    if (Input::isKeyDown(SDLK_d))
//    {
//        //animationSpeed = origSpeed;
//        setAnimationRow(1);
//    }
//    if (Input::isKeyDown(SDLK_a))
//    {
//        //animationSpeed = origSpeed;
//        setAnimationRow(3);
//    }
//    //else animationSpeed = 1000;
//    
//    
//    
//}
//
//void SpriteComponent::draw() {
//    auto body = getParent().get<BodyComponent>();
//    if (body) {
//        // Define the source rectangle for the current frame
//        SDL_Rect srcRect = { currentFrame * width, currentRow * height, width, height };
//
//        // Define the destination rectangle for rendering (position on screen)
//        SDL_Rect dst = { static_cast<int>(body->x()), static_cast<int>(body->y()), width, height };
//
//        // Transform the destination rectangle to account for the camera's position
//        SDL_Rect transformedDst = Engine::camera.transformRect(dst);
//
//        // Render the texture using the transformed rectangle
//        SDL_RenderCopy(Engine::getRenderer(), texture, &srcRect, &transformedDst);
//    }
//}
//
//void SpriteComponent::setAnimationRow(int row) {
//    if (row >= 0 && row < 4) {  // Ensure it's a valid row (0-3)
//        currentRow = row;
//        currentFrame = 0;  // Reset to the first frame of the new row
//    }
//}
//
//void SpriteComponent::setAnimationSpeed(int speed) {
//    animationSpeed = speed;
//}
