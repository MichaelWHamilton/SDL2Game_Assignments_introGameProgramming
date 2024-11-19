#include "CollisionListener.h"

// Called when two fixtures begin to touch
void CollisionListener::BeginContact(b2Contact* contact){
    auto* fixtureA = contact->GetFixtureA();
    auto* fixtureB = contact->GetFixtureB();

    // Retrieve user data (usually the parent GameObject or component pointer)
    auto* bodyA = fixtureA->GetBody();
    auto* bodyB = fixtureB->GetBody();

    std::cout << "Collision detected between two bodies!\n";
    // Optional: Retrieve user data from bodies for more context
    /*auto* dataA = static_cast<void*>(bodyA->GetUserData().pointer);
    auto* dataB = static_cast<void*>(bodyB->GetUserData().pointer);*/
    // Add your collision handling logic here.
}

// Called when two fixtures stop touching
void CollisionListener::EndContact(b2Contact* contact){
    auto* fixtureA = contact->GetFixtureA();
    auto* fixtureB = contact->GetFixtureB();

    std::cout << "Collision ended between two bodies!\n";
    // Optional: Add logic for when bodies stop colliding
}

