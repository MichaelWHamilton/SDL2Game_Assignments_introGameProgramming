#pragma once
#include "Component.h"
#include <iostream>
#include "GameObject.h"

class BodyComponent : public Component {
public:
    
    BodyComponent(GameObject& parentObj, double x, double y, double width, double height);

    double& getX();
    double& getY();
    double& getWidth();
    double& getHeight();
    double& getVx();
    double& getVy();

    void update() override;

    void draw() override;

private:
    double m_width, m_height, m_xPos, m_yPos, m_xVel, m_yVel;  // Position
};
