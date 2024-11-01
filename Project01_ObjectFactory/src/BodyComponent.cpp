#include "BodyComponent.h"

BodyComponent::BodyComponent(GameObject& parentObj, double x, double y)
    : Component(parentObj), xPos(x), yPos(y), xVel(x), yVel(y) {}

double& BodyComponent::x() { return xPos; }
double& BodyComponent::y() { return yPos; }
double& BodyComponent::vx() { return xVel; }
double& BodyComponent::vy() { return yVel; }

void BodyComponent::update() {
    //// Example: Move the object downwards
    //y += 1.0f;
    //std::cout << "BodyComponent updated position: (" << x << ", " << y << ")\n";
}

void BodyComponent::draw() {
    // Drawing logic would go here (if needed)
}

