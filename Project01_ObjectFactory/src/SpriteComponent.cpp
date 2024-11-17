#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey)
    : Component(parent), m_texture(nullptr), m_width(64), m_height(64) {
    m_texture = Textures::get(textureKey);
    if (!m_texture) {
        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
    }
}
SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey, int width, int height)
    : Component(parent), m_texture(nullptr), m_width(width), m_height(height) {
    m_texture = Textures::get(textureKey);
    if (!m_texture) {
        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
    }
}

void SpriteComponent::update(){}

void SpriteComponent::draw() {
    auto body = getParent().getComponent<BodyComponent>();
    if (body) {
        // Define destination rectangle based on the position from the BodyComponent
        SDL_Rect dst = {static_cast<int>(body->getX()), static_cast<int>(body->getY()), m_width, m_height};

        // Transform the destination rectangle to account for the view (camera) position and scale
        SDL_Rect transformedDst = Engine::camera.transformRect(dst);

        // Render the texture using the transformed rectangle
        SDL_RenderCopy(Engine::getRenderer(), m_texture, nullptr, &transformedDst);
    }
}
