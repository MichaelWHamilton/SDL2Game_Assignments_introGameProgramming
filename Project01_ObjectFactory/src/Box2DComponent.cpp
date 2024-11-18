#include "Box2DComponent.h"

Box2DComponent::Box2DComponent(GameObject& parent, b2World& world)
    :Component(parent), m_world(world), m_body(nullptr)
{
    auto bodyComp = parent.getComponent<BodyComponent>();
    if (!bodyComp) {
        throw std::runtime_error("Box2DComponent requires a BodyComponent in the same GameObject.");
        exit;
    }

    // Create a Box2D body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(bodyComp->getX(), bodyComp->getY());
    m_body = world.CreateBody(&bodyDef);

    // Attach a rectangular fixture
    b2PolygonShape boxShape;
    boxShape.SetAsBox(bodyComp->getWidth() / 2.0f, bodyComp->getWidth() / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_body->CreateFixture(&fixtureDef);
}

Box2DComponent::~Box2DComponent() {
    if (m_body) {
        m_world.DestroyBody(m_body);
    }
}

void Box2DComponent::update() {
    auto bbody = getParent().getComponent<BodyComponent>();
    if (bbody) {
        const b2Vec2& pos = { (float)bbody->getX(), (float)bbody->getY() };
        // Sync BodyComponent with Box2D body
        //const b2Vec2& pos = body->GetPosition();
        //body->SetPosition(pos.x, pos.y);
        //body->SetAngle(body->GetAngle() * (180.0f / b2_pi)); // Radians to degrees
        std::cout << "Body x: " << bbody->getX() << "Body y:" << bbody->getY();
        std::cout << "Box Body x: " << pos.x << "Box Body y: " << pos.y;
    }
}

b2Body* Box2DComponent::getBody() {
    return m_body;
}
