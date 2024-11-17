#pragma once
#include "Component.h"
#include <iostream>
#include "GameObject.h"

class BodyComponent : public Component {
public:
    

    BodyComponent(GameObject& parentObj, double x, double y);


    double& getX();
    double& getY();
    double& getVx();
    double& getVy();

    void update() override;

    void draw() override;

private:
    double m_xPos, m_yPos, m_xVel, m_yVel;  // Position
};
