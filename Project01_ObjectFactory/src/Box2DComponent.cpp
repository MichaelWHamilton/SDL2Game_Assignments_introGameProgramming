#include "Box2DComponent.h"
#include "ComponentsInclude.h"

Box2DComponent::Box2DComponent(GameObject& parent)
    :Component(parent), m_body(nullptr)
{
    m_body = Engine::registerGameObject(parent);

    if (m_body) {
        auto bodyComponent = parent.getComponent<BodyComponent>();

        // Define the shape and attach it as a fixture
        b2PolygonShape boxShape;
        boxShape.SetAsBox(bodyComponent->getWidth() / 2.0f, bodyComponent->getHeight() / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        m_body->CreateFixture(&fixtureDef);
    }



    //auto bodyComp = parent.getComponent<BodyComponent>();
    //if (!bodyComp) {
    //    throw std::runtime_error("Box2DComponent requires a BodyComponent in the same GameObject.");
    //    exit;
    //}

    //// Create a Box2D body
    //b2BodyDef bodyDef;

    //switch (bodyType){
    //case box2DDynamic:
    //    bodyDef.type = b2_dynamicBody;
    //    break;
    //case box2DStatic:
    //    bodyDef.type = b2_staticBody;
    //    break;
    //case box2DKinematic:
    //    bodyDef.type = b2_kinematicBody;
    //    break;
    //}

    //bodyDef.type = b2_dynamicBody;
    //bodyDef.position.Set(bodyComp->getX(), bodyComp->getY());
    //m_body = Engine::world.CreateBody(&bodyDef);

    //// Attach a rectangular fixture
    //b2PolygonShape boxShape;
    //boxShape.SetAsBox(bodyComp->getWidth() / 2.0f, bodyComp->getWidth() / 2.0f);

    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = &boxShape;
    //fixtureDef.density = 1.0f;
    //fixtureDef.friction = 0.3f;

    //m_body->CreateFixture(&fixtureDef);
}

Box2DComponent::~Box2DComponent() {
    if (m_body) {
        Engine::m_world.DestroyBody(m_body);
    }
}

void Box2DComponent::update() {
    //auto bbody = getParent().getComponent<BodyComponent>();
    //if (bbody) {
    //    const b2Vec2& pos = { (float)bbody->getX(), (float)bbody->getY() };
    //    // Sync BodyComponent with Box2D body
    //    //const b2Vec2& pos = body->GetPosition();
    //    //body->SetPosition(pos.x, pos.y);
    //    //body->SetAngle(body->GetAngle() * (180.0f / b2_pi)); // Radians to degrees
    //    std::cout << "Body x: " << bbody->getX() << "Body y:" << bbody->getY();
    //    std::cout << "Box Body x: " << pos.x << "Box Body y: " << pos.y;
    //}
    float timeStep = 1.0f / 60.0f; // 60 FPS
    int velocityIterations = 8;   // Recommended: 8 velocity iterations
    int positionIterations = 3;   // Recommended: 3 position iterations
    Engine::m_world.Step(timeStep, velocityIterations, positionIterations);

    // Sync Box2D bodies with BodyComponents
    for (auto& gameObject : Engine::mapGameObjects) {
        auto bodyComp = gameObject.second->getComponent<BodyComponent>();
        auto box2dComp = gameObject.second->getComponent<Box2DComponent>();

        if (bodyComp && box2dComp) {
            const b2Body* b2Body = box2dComp->getBody();

            // Update the BodyComponent with the new Box2D body position
            bodyComp->setX(b2Body->GetPosition().x);
            bodyComp->setY(b2Body->GetPosition().y);

            // Optionally update velocities or other properties
            //bodyComp->setVx(b2Body->GetLinearVelocity().x);
            //bodyComp->setVy(b2Body->GetLinearVelocity().y);
        }
    }
}

b2Body* Box2DComponent::getBody() {
    return m_body;
}
