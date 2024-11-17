#pragma once
#include "Component.h"
#include <cmath> // For sin function
#include <iostream>
#include "BodyComponent.h"

class MoveUpAndDownComponent : public Component {
private:
    double m_amplitude; // Distance to swing (half of the total distance)
    double m_speed; // Speed of the swing
    double m_time; // Time counter for the oscillation

public:
    MoveUpAndDownComponent(GameObject& parentObj, double amplitude, double speed)
        : Component(parentObj), m_amplitude(amplitude), m_speed(speed), m_time(0.0) {}

    void update() override {
        m_time += m_speed; // Increment time based on speed
        
        auto body = getParent().getComponent<BodyComponent>();
        body->getY() += m_amplitude * std::sin(m_time);
    }

    void draw() override {
        
    }
};
