#pragma once
#include "Component.h"
#include <cmath>
#include <iostream>

class GameObject;
class MoveUpAndDownComponent : public Component {
private:
    double m_amplitude; // Distance to swing (half of the total distance)
    double m_speed; // Speed of the swing
    double m_time; // Time counter for the oscillation

public:
    MoveUpAndDownComponent(GameObject& parentObj, double amplitude, double speed);

    void update() override;

    void draw() override;
};
