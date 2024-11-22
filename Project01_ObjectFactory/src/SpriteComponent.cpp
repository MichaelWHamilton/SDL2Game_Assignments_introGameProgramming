#include "SpriteComponent.h"
#include "ComponentsInclude.h"
SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey, std::string name)
    : Component(parent), m_texture(nullptr), m_name(name){
    m_texture = Textures::get(textureKey);
    if (!m_texture) {
        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
    }
}
//SpriteComponent::SpriteComponent(GameObject& parent, std::string textureKey, int width, int height)
//    : Component(parent), m_texture(nullptr){
//    m_texture = Textures::get(textureKey);
//    if (!m_texture) {
//        SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
//    }
//}

void SpriteComponent::update(){
    
    //std::cout << "Sprite update function called!" << std::endl;
}

void SpriteComponent::draw() {
    auto body = getParent().getComponent<BodyComponent>();
    if (body) {
        // Define destination rectangle based on the position from the BodyComponent
        //SDL_Rect dst = {static_cast<int>(body->getBody()->GetPosition().x), static_cast<int>(body->getBody()->GetPosition().y), static_cast<int>(body->getWidth()), static_cast<int>(body->getHeight()) };
        int x = static_cast<int>(body->getBody()->GetPosition().x );
        int y = static_cast<int>(body->getBody()->GetPosition().y );

        // Define SDL rectangle (in pixels)
        SDL_Rect rect;
        rect.x = x - static_cast<int>(body->m_width);
        rect.y = y - static_cast<int>(body->m_height);
        //rect.x = x - static_cast<int>(body->m_width / 2);
        //rect.y = y - static_cast<int>(body->m_height / 2);
        rect.w = static_cast<int>(body->m_width );
        rect.h = static_cast<int>(body->m_height );

        if (Input::isKeyDown(SDLK_LEFT))
        {
            flip = SDL_FLIP_HORIZONTAL;
        }

        if (Input::isKeyDown(SDLK_RIGHT))
        {
            flip = SDL_FLIP_NONE;
        }
        //if (body->m_body->GetLinearVelocity().x <= -0.01) {  // Facing left
        //    flip = SDL_FLIP_HORIZONTAL;
        //}
        //
        //else { flip = SDL_FLIP_NONE;
        //}

        // Transform the destination rectangle to account for the view (camera) position and scale
        SDL_Rect transformedDst = Engine::camera.transformRect(rect);

        // Render the texture using the transformed rectangle
        //SDL_RenderCopy(Engine::getRenderer(), m_texture, nullptr, &transformedDst);
        SDL_RenderCopyEx(Engine::getRenderer(), m_texture, nullptr, &transformedDst, 0.0, nullptr, flip);
    }
}
std::string SpriteComponent::getName() {
    return m_name;
}
//SDL_RendererFlip SpriteComponent::flip = SDL_FLIP_NONE;
