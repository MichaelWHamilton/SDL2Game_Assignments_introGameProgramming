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
        int x = static_cast<int>(body->getBody()->GetPosition().x );
        int y = static_cast<int>(body->getBody()->GetPosition().y );

        SDL_Rect rect;
        rect.x = x - static_cast<int>(body->m_width/2);
        rect.y = y - static_cast<int>(body->m_height/2);
        
        rect.w = static_cast<int>(body->m_width );
        rect.h = static_cast<int>(body->m_height );

        if (Input::isKeyDown(SDLK_LEFT ))//|| SDLK_a
        {
            flip = SDL_FLIP_HORIZONTAL;
        }
        if (Input::isKeyDown(SDLK_a))//|| SDLK_a
        {
            flip = SDL_FLIP_HORIZONTAL;
        }

        if (Input::isKeyDown(SDLK_RIGHT  ))//|| SDLK_d
        {
            flip = SDL_FLIP_NONE;
        }
        if (Input::isKeyDown(SDLK_d))//|| SDLK_d
        {
            flip = SDL_FLIP_NONE;
        }
        
        SDL_Rect transformedDst = Engine::camera.transformRect(rect);

        // Render the texture using the transformed rectangle
        //SDL_RenderCopy(Engine::getRenderer(), m_texture, nullptr, &transformedDst);
        SDL_RenderCopyEx(Engine::getRenderer(), m_texture, nullptr, &transformedDst, 0.0, nullptr, flip);
    }
}
std::string SpriteComponent::getName() {
    return m_name;
}

