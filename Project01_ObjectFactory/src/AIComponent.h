#pragma once
#include "Component.h"
#include "BodyComponent.h"


//DROPPED FOR NOW
class AIComponent : public Component {
private:
    double speed; // Speed for the AI movement

public:
    AIComponent(GameObject& parentObj, double speedValue)
        : Component(parentObj), speed(speedValue) {}

    void update() override {
        
        auto body = getParent().get<BodyComponent>();
        body->y() += speed; 
        body->x() += speed; 
    }
    void draw() override {}
};
