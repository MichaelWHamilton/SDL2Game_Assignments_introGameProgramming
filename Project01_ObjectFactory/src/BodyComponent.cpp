#include "BodyComponent.h"
#include "ComponentsInclude.h"
BodyComponent::BodyComponent(GameObject& parent, double x, double y, double width, double height)
    : Component(parent), m_xPos(x), m_yPos(y), m_xVel(0), m_yVel(0), m_width(width), m_height(height), m_body(nullptr) {

    /*auto bodyComp = parent.getComponent<BodyComponent>();
    if (!bodyComp) {
        throw std::runtime_error("Box2DComponent requires a BodyComponent in the same GameObject.");
        exit;
    }*/

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
    bodyDef.position.Set((float)m_xPos, (float)m_yPos);
    m_body = Engine::m_world.CreateBody(&bodyDef);

    // Attach a rectangular fixture
    b2PolygonShape boxShape;
    boxShape.SetAsBox((float)m_width / 2.0f, (float)m_height / 2.0f);//add scale

    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_body->GetUserData().pointer = (uintptr_t)this;
    m_body->CreateFixture(&fixtureDef);

    // Set SDL rect dimensions in pixels
        //rect.w = static_cast<int>(width);
        //rect.h = static_cast<int>(height);

}

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
    //auto obj = getParent().getComponent<SpriteComponent>();
    //auto boxBody = getParent().getComponent<Box2DComponent>();
    std::cout << "Body update function called!" << std::endl;

    //m_xPos = boxBody->getBody()->GetPosition().x;
    //m_yPos = boxBody->getBody()->GetPosition().y;
    //std::cout << obj->getName() << " X Y coords: ( " << m_xPos << " , " << m_yPos << " )";
    //m_xPos = m_body->GetPosition().x;
    //m_yPos = m_body->GetPosition().y;
}

void BodyComponent::draw() {
    // Drawing logic would go here (if needed)
}

