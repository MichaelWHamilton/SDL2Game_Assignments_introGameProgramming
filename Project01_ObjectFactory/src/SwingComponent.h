#pragma once
#include "Component.h"
#include <cmath> // For sin function
#include <iostream>
#include "BodyComponent.h"

class SwingComponent : public Component {
private:
    double amplitude; // Distance to swing (half of the total distance)
    double speed; // Speed of the swing
    double time; // Time counter for the oscillation

public:
    SwingComponent(GameObject& parentObj, double amplitude, double speed)
        : Component(parentObj), amplitude(amplitude), speed(speed), time(0.0) {}

    void update() override {
        time += speed; // Increment time based on speed
        
        auto body = getParent().get<BodyComponent>();
        body->y() += amplitude * std::sin(time);
    }

    void draw() override {
        
    }
};
