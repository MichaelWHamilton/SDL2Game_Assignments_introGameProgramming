#pragma once
#include "Component.h"
#include <iostream>
#include "box2d/box2d.h"

class GameObject;
class BodyComponent : public Component {
public:
    
    BodyComponent(GameObject& parent, double x, double y, double width, double height);

    double& getX();
    double& getY();
    double& getWidth();
    double& getHeight();
    double& getVx();
    double& getVy();


    void setX(double x);
    void setY(double y);
    void setVx(double vx);
    void setVy(double xy);

    void update() override;

    void draw() override;
    b2Body* m_body;
private:
    double m_width, m_height, m_xPos, m_yPos, m_xVel, m_yVel;  // Position
    
};
