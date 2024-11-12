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

