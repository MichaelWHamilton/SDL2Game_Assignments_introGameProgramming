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

    // Create a Box2D body
    b2BodyDef bodyDef;
    Box2DBodyType bodyType = box2DDynamic;
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
    }

    bodyDef.position.Set((float)bodyComp->getX(), (float)bodyComp->getY());
    m_body = Engine::m_world.CreateBody(&bodyDef);

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
        Engine::m_world.DestroyBody(m_body);
    }
}

void Box2DComponent::update() {
        
    auto bodyComp = getParent().getComponent<BodyComponent>();
    auto box2dComp = getParent().getComponent<Box2DComponent>();

    if (bodyComp && box2dComp) {
        //const b2Body* b2Body = box2dComp->getBody();
        

        // Optionally update velocities or other properties
        //bodyComp->setVx(b2Body->GetLinearVelocity().x);
        //bodyComp->setVy(b2Body->GetLinearVelocity().y);
    }
    
}

b2Body* Box2DComponent::getBody() const{
    return m_body;
}
