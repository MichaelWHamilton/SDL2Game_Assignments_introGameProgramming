#include "BodyComponent.h"
#include "ComponentsInclude.h"
BodyComponent::BodyComponent(GameObject& parent, double x, double y, double width, double height, int bodyType)
    : Component(parent), m_width(width), m_height(height), m_body(nullptr) {

    // Create a Box2D body
    b2BodyDef bodyDef;
    
    //// Convert to pixels for SDL
    //int xpos = static_cast<int>(x * Engine::scale);
    //int ypos = static_cast<int>(y * Engine::scale);

    //// Define SDL rectangle (in pixels)
    ////SDL_Rect rect;
    //rect.x = xpos - static_cast<int>(m_width * Engine::scale / 2);
    //rect.y = ypos - static_cast<int>(m_height * Engine::scale / 2);
    //rect.w = static_cast<int>(m_width * Engine::scale);
    //rect.h = static_cast<int>(m_height * Engine::scale);

    switch (bodyType) {
    case b2_dynamic:
        bodyDef.type = b2_dynamicBody;
        break;
    case b2_static:
        bodyDef.type = b2_staticBody;
        break;
    case b2_kinematic:
        bodyDef.type = b2_kinematicBody;
        break;
    }
    //bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((float)x , (float)y * 1.0f );
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.0f;
    m_body = Engine::m_world.CreateBody(&bodyDef);
    if (bodyDef.type == b2_dynamicBody)
    {
        //m_body->SetLinearVelocity(b2Vec2(0.0f,10.0f));
    }
    // Attach a rectangular fixture
    b2PolygonShape boxShape;
    boxShape.SetAsBox((float)m_width  /  2.0f, (float)m_height  /  2.0f);//add scale

    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    //std::cout << parent.getComponent<SpriteComponent>()->getName();
    
        fixtureDef.filter.maskBits = 0x0000;
    
    
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
    // Drawing logic

}

