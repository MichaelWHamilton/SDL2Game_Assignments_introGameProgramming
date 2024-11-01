#include "CharacterControllerComponent.h"

CharacterControllerComponent::CharacterControllerComponent(GameObject& owner, float speed)
    : Component(owner), speed(speed) {}

void CharacterControllerComponent::update(){
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_W]) { move(0, -1); }
    if (state[SDL_SCANCODE_S]) { move(0, 1); }
    if (state[SDL_SCANCODE_A]) { move(-1, 0); }
    if (state[SDL_SCANCODE_D]) { move(1, 0); }
}

void CharacterControllerComponent::draw(){}

void CharacterControllerComponent::move(float dx, float dy) {
    auto body = getParent().get<BodyComponent>();
    if (body) {
        body->x() += dx * speed;
        body->y() += dy * speed;
    }
}
