#pragma once
#include "Component.h"
#include <iostream>
#include "GameObject.h"

class BodyComponent : public Component {
public:
    double xPos, yPos, xVel, yVel;  // Position

    BodyComponent(GameObject& parentObj, double x, double y);


    double& x();
    double& y();
    double& vx();
    double& vy();

    void update() override;

    void draw() override;
};
