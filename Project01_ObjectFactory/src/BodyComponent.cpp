#include "BodyComponent.h"

BodyComponent::BodyComponent(GameObject& parentObj, double x, double y)
    : Component(parentObj), m_xPos(x), m_yPos(y), m_xVel(x), m_yVel(y) {}

double& BodyComponent::getX() { return m_xPos; }
double& BodyComponent::getY() { return m_yPos; }
double& BodyComponent::getVx() { return m_xVel; }
double& BodyComponent::getVy() { return m_yVel; }

void BodyComponent::update() {
    //// Example: Move the object downwards
    //y += 1.0f;
    //std::cout << "BodyComponent updated position: (" << x << ", " << y << ")\n";
}

void BodyComponent::draw() {
    // Drawing logic would go here (if needed)
}

