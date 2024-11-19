#include "BodyComponent.h"
#include "ComponentsInclude.h"
BodyComponent::BodyComponent(GameObject& parent, double x, double y, double width, double height)
    : Component(parent), m_width(width), m_height(height), m_body(nullptr) {

    // Create a Box2D body
    b2BodyDef bodyDef;
    /*Box2DBodyType bodyType = box2DDynamic;
    switch (bodyType) {
    case box2DDynamic:
        bodyDef.type = b2_dynamicBody;
        break;
    case box2DStatic:
        bodyDef.type = b2_staticBody;
        break;
    case box2DKinematic:
        bodyDef.type = b2_kinematicBody;
        break;
    }*/
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((float)x, (float)y);
    bodyDef.linearDamping = 0.0f; // No resistance
    m_body = Engine::m_world.CreateBody(&bodyDef);

    // Attach a rectangular fixture
    b2PolygonShape boxShape;
    boxShape.SetAsBox((float)m_width /  2.0f, (float)m_height / 2.0f);//add scale

    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.0f;

    m_body->GetUserData().pointer = (uintptr_t)this;
    m_body->CreateFixture(&fixtureDef);

    // Set SDL rect dimensions in pixels
        //rect.w = static_cast<int>(width);
        //rect.h = static_cast<int>(height);

}

//double& BodyComponent::getX() { return m_xPos; }
//double& BodyComponent::getY() { return m_yPos; }
double& BodyComponent::getWidth() { return m_width; }
double& BodyComponent::getHeight() { return m_height; }
//double& BodyComponent::getVx() { return m_xVel; }
//double& BodyComponent::getVy() { return m_yVel; }

//void BodyComponent::setX(double x) { m_xPos = x; };
//void BodyComponent::setY(double y) { m_yPos = y; };

//void BodyComponent::setVx(double vx) { m_xVel=vx; }
//void BodyComponent::setVy(double vy) { m_yVel=vy; }

b2Body* BodyComponent::getBody() { return m_body; };

void BodyComponent::update() {
    auto sprite = getParent().getComponent<SpriteComponent>();
    std::cout << "Object Name: " << sprite->getName() << std::endl;
    std::cout << "Body comp update function called!" << std::endl;
    //std::cout << "x:" << m_xPos << " y: " << m_yPos << std::endl;;
    std::cout << "box2d coords" << std::endl;
    std::cout << "x:" << m_body->GetPosition().x << " y:"  << m_body->GetPosition().y << std::endl;
    //m_body->SetTransform(b2Vec2(m_xPos, m_yPos), 0);
    //m_xPos = m_body->GetPosition().x;
   // m_yPos = m_body->GetPosition().y;
}

void BodyComponent::draw() {
    // Drawing logic would go here (if needed)
}

