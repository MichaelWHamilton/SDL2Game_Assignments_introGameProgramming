#include "Box2DComponent.h"
#include "ComponentsInclude.h"

Box2DComponent::Box2DComponent(GameObject& parent)
    :Component(parent), m_body(nullptr)
{
    auto bodyComp = parent.getComponent<BodyComponent>();
    if (!bodyComp) {
        throw std::runtime_error("Box2DComponent requires a BodyComponent in the same GameObject.");
        exit;
    }
    std::cout << " creating body " << std::endl;
    // Create a Box2D body
    b2BodyDef bodyDef;
    Box2DBodyType bodyType = box2DDynamic;
    switch (bodyType) {
    case box2DDynamic:
        std::cout << parent.getComponent<SpriteComponent>()->getName() << " " << " dynamic" << std::endl;
        bodyDef.type = b2_dynamicBody;
        break;
    case box2DStatic:
        bodyDef.type = b2_staticBody;
        std::cout << parent.getComponent<SpriteComponent>()->getName() << " " << " static" << std::endl;
        break;
    case box2DKinematic:
        bodyDef.type = b2_kinematicBody;
        std::cout << parent.getComponent<SpriteComponent>()->getName() << " " << " kinematic" << std::endl;
        break;
    }
    
    //bodyDef.position.Set((float)bodyComp->getX(), (float)bodyComp->getY());
    m_body = Engine::m_world->CreateBody(&bodyDef);

    // Attach a rectangular fixture
    b2PolygonShape boxShape;
    boxShape.SetAsBox((float)bodyComp->getWidth() / 2.0f, (float)bodyComp->getWidth() / 2.0f);//add scale

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

Box2DComponent::~Box2DComponent() {
    if (m_body) {
        Engine::m_world->DestroyBody(m_body);
    }
}

void Box2DComponent::update() {
    
    auto bodyComp = getParent().getComponent<BodyComponent>();
    auto box2dComp = getParent().getComponent<Box2DComponent>();
    std::cout << "box2d comp update called" << std::endl;

    std::cout << 'x:' << m_body->GetPosition().x << ' y: ' << m_body->GetPosition().y;
    if (bodyComp && box2dComp) {
        
    }
    
}

b2Body* Box2DComponent::getBody() const{
    return m_body;
}
