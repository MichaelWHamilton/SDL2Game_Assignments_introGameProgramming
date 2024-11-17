#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include <box2d/box2d.h>
#include <memory>

class Box2DComponent : public Component {
private:
    b2Body* body;
    b2World* world;
    BodyComponent* bodyComponent; // Reference to synchronize position

public:
    Box2DComponent(GameObject& parent, b2World* physicsWorld, BodyComponent* associatedBody, float posX, float posY, float width, float height);

    ~Box2DComponent();

    void update() override;

    b2Body* getBody();
};
