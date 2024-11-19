#include "CharacterControllerComponent.h"
#include "ComponentsInclude.h"

CharacterControllerComponent::CharacterControllerComponent(GameObject& owner, float speed)
    : Component(owner), m_speed(speed) {}

void CharacterControllerComponent::update(){
    /*const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_W]) { move(0, -1); }
    if (state[SDL_SCANCODE_S]) { move(0, 1); }
    if (state[SDL_SCANCODE_A]) { move(-1, 0); }
    if (state[SDL_SCANCODE_D]) { move(1, 0); }*/

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    // Start with zero velocity
    b2Vec2 velocity(0.0f, 0.0f);

    // Adjust velocity based on input
    if (state[SDL_SCANCODE_UP]) {
        velocity.y = -m_speed;  // Move up
    }
    if (state[SDL_SCANCODE_DOWN]) {
        velocity.y = m_speed;  // Move down
    }
    if (state[SDL_SCANCODE_LEFT]) {
        velocity.x = -m_speed;  // Move left
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        velocity.x = m_speed;  // Move right
    }

    // Set the body's linear velocity
    auto body = getParent().getComponent<BodyComponent>();
    body->m_body->SetLinearVelocity(velocity);

    // Synchronize position variables for the sprite update
    body->setX(body->m_body->GetPosition().x);
    body->setY(body->m_body->GetPosition().y);
}

void CharacterControllerComponent::draw(){}

void CharacterControllerComponent::move(float dx, float dy) {
    auto body = getParent().getComponent<BodyComponent>();
    if (body) {
        //body->m_body->SetLinearVelocity();
        //body->getY() += dy * m_speed;
    }
}
