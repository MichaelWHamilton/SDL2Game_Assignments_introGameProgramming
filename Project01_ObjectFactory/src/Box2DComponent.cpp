#include "Box2DComponent.h"

Box2DComponent::Box2DComponent(GameObject& parent, b2World* physicsWorld, BodyComponent* associatedBody, float posX, float posY, float width, float height)
    :Component(parent), world(physicsWorld), bodyComponent(associatedBody)
{
    // Create a Box2D body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posX, posY);
    body = world->CreateBody(&bodyDef);

    // Attach a rectangular fixture
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2.0f, height / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Box2DComponent::~Box2DComponent() {
    if (body) {
        world->DestroyBody(body);
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
    return body;
}
