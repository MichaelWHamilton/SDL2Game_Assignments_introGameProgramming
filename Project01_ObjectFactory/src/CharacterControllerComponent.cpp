//#include "CharacterControllerComponent.h"
//#include "ComponentsInclude.h"
//
//CharacterControllerComponent::CharacterControllerComponent(GameObject& owner, float speed)
//    : Component(owner), m_speed(speed) {}
//
//void CharacterControllerComponent::update(){
//
//    std::cout << "charactercontroller update called" << std::endl;
//
//
//    const Uint8* state = SDL_GetKeyboardState(nullptr);
//    if (state[SDL_SCANCODE_W]) { move(0, -1); }
//    if (state[SDL_SCANCODE_S]) { move(0, 1); }
//    if (state[SDL_SCANCODE_A]) { move(-1, 0); }
//    if (state[SDL_SCANCODE_D]) { move(1, 0); }
//
//    //const Uint8* state = SDL_GetKeyboardState(nullptr);
//
//    //// Start with zero velocity
//    //b2Vec2 velocity(0.0f, 0.0f);
//
//    //// Adjust velocity based on input
//    //if (state[SDL_SCANCODE_UP]) {
//    //    velocity.y = -m_speed;  // Move up
//    //}
//    //if (state[SDL_SCANCODE_DOWN]) {
//    //    velocity.y = m_speed;  // Move down
//    //}
//    //if (state[SDL_SCANCODE_LEFT]) {
//    //    velocity.x = -m_speed;  // Move left
//    //}
//    //if (state[SDL_SCANCODE_RIGHT]) {
//    //    velocity.x = m_speed;  // Move right
//    //}
//
//    //// Set the body's linear velocity
//    //auto body = getParent().getComponent<BodyComponent>();
//    //body->m_body->SetLinearVelocity(velocity);
//
//    //// Synchronize position variables for the sprite update
//    //body->setX(body->m_body->GetPosition().x);
//    //body->setY(body->m_body->GetPosition().y);
//}
//
//void CharacterControllerComponent::draw(){}
//
//void CharacterControllerComponent::move(float dx, float dy) {
//    auto body = getParent().getComponent<BodyComponent>();
//    if (body) {
//        //body->m_body->SetLinearVelocity();
//        //body->getX() += dx * m_speed;
//        //body->getY() += dy * m_speed;
//        /*b2Vec2* x = new b2Vec2(dx, dy);
//        body->m_body->SetLinearVelocity(*x);*/
//    }
//}

#include "CharacterControllerComponent.h"
#include "ComponentsInclude.h"
CharacterControllerComponent::CharacterControllerComponent(GameObject& parent, float speed)
    : Component(parent), m_speed(speed), m_jumpForce(50.0f) {}

void CharacterControllerComponent::update() {
    //auto body = getParent().getComponent<BodyComponent>();
    //if (!body) return; // No body component to update

    //// get velocity
    ////b2Vec2 velocity = body->m_body->GetLinearVelocity();
    //b2Vec2 velocity(0.0f, body->m_body->GetLinearVelocity().y);
    //// Horizontal movement
    //if (Input::isKeyDown(SDLK_LEFT)) {
    //    std::cout << "left key pressed" << std::endl;
    //    velocity.x = -m_speed*10;
    //}
    //else if (Input::isKeyDown(SDLK_RIGHT)) {
    //    std::cout << "right key pressed" << std::endl;
    //    velocity.x = m_speed*10;
    //}
    //else {
    //    velocity.x = 0.0f;
    //}

    //if (Input::isKeyDown(SDLK_e)) {
    //    std::cout << "********e key pressed***********" << std::endl;
    //    Engine::spawnObject();
    //}

    // //Jumping
    //if (Input::isKeyDown(SDLK_SPACE) && isGrounded()) {
    //    std::cout << "grounded and pressing space" << std::endl;
    //    velocity.y = -m_jumpForce; 
    //}

    //body->m_body->SetLinearVelocity(velocity);


    /*  Switching to top down game view, new movement including up down*/

    auto body = getParent().getComponent<BodyComponent>()->getBody();
    if (!body) return;

    b2Vec2 velocity(0.0f, 0.0f);

    // Horizontal movement
    if (Input::isKeyDown(SDLK_LEFT) || Input::isKeyDown(SDLK_a)) {
        //velocity.x = -m_speed; // Move left
       // body->m_body->SetLinearVelocity(velocity);

        float velocityX = -m_speed / Engine::scale *10;
        float velocityY = m_speed / Engine::scale ;
        body->SetLinearVelocity(b2Vec2(velocityX, 0.0f));
    }
    else if (Input::isKeyDown(SDLK_RIGHT) || Input::isKeyDown(SDLK_d)) {
        velocity.x = m_speed; // Move right
        float velocityX = m_speed / Engine::scale * 10;
        float velocityY = m_speed / Engine::scale ;
        body->SetLinearVelocity(b2Vec2(velocityX, 0.0f));
    }

    // Vertical movement
    else if (Input::isKeyDown(SDLK_UP) || Input::isKeyDown(SDLK_w)) {
        velocity.y = -m_speed; // Move up
        float velocityX = m_speed / Engine::scale ;
        float velocityY = -m_speed / Engine::scale * 10;
        body->SetLinearVelocity(b2Vec2(0.0f, velocityY));
    }
    else if (Input::isKeyDown(SDLK_DOWN) || Input::isKeyDown(SDLK_s)) {
        velocity.y = m_speed; // Move down
        float velocityX = m_speed / Engine::scale ;
        float velocityY = m_speed / Engine::scale * 10;
        body->SetLinearVelocity(b2Vec2(0.0f, velocityY));
    }
    else body->SetLinearVelocity(b2Vec2(0.0f,0.0f));

    
    // Set the body's linear velocity
    //body->m_body->SetLinearVelocity(velocity);

    //b2Vec2 position = body->m_body->GetPosition();

    //// Update only the horizontal position (X) based on user input
    //if (Input::isKeyDown(SDLK_LEFT)) {
    //    position.x -= m_speed; // Move left
    //}
    //else if (Input::isKeyDown(SDLK_RIGHT)) {
    //    position.x += m_speed; // Move right
    //}

    //// Update only the vertical position (Y) based on user input
    //if (Input::isKeyDown(SDLK_UP)) {
    //    position.y -= m_speed; // Move up
    //}
    //else if (Input::isKeyDown(SDLK_DOWN)) {
    //    position.y += m_speed; // Move down
    //}

    //// Set the new position directly
    //body->m_body->SetTransform(position, body->m_body->GetAngle());

}

bool CharacterControllerComponent::isGrounded() {
    auto body = getParent().getComponent<BodyComponent>();
    if (!body) return false; 
    b2Vec2 velocity = body->m_body->GetLinearVelocity();

    //if (std::abs(velocity.y) < 0.01f) return true;
    //else return false;
    return (std::abs(velocity.y) < 0.01f); // No vertical movement means grounded
}
void CharacterControllerComponent::draw() {};
