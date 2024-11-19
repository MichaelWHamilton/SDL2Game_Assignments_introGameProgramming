#include "BodyComponent.h"
#include "ComponentsInclude.h"
BodyComponent::BodyComponent(GameObject& parentObj, double x, double y, double width, double height)
    : Component(parentObj), m_xPos(x), m_yPos(y), m_xVel(0), m_yVel(0), m_width(width), m_height(height) {}

double& BodyComponent::getX() { return m_xPos; }
double& BodyComponent::getY() { return m_yPos; }
double& BodyComponent::getWidth() { return m_width; }
double& BodyComponent::getHeight() { return m_height; }
double& BodyComponent::getVx() { return m_xVel; }
double& BodyComponent::getVy() { return m_yVel; }

void BodyComponent::setX(double x) { m_xPos = x; };
void BodyComponent::setY(double y) { m_yPos = y; };

void BodyComponent::setVx(double vx) { m_xVel=vx; }
void BodyComponent::setVy(double vy) { m_yVel=vy; }

void BodyComponent::update() {
    //// Example: Move the object downwards
    //y += 1.0f;
    //std::cout << "BodyComponent updated position: (" << x << ", " << y << ")\n";
    auto obj = getParent().getComponent<SpriteComponent>();
    
    std::cout << "Body update function called!" << std::endl;
    std::cout << obj->getName() << " X Y coords: ( " << m_xPos << " , " << m_yPos << " )";
}

void BodyComponent::draw() {
    // Drawing logic would go here (if needed)
}

