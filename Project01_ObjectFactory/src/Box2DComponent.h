#pragma once
#include "Component.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include <box2d/box2d.h>
#include <memory>

class Box2DComponent : public Component {
private:
    b2Body* m_body;
    b2World& m_world;
public:
    Box2DComponent(GameObject& parent, b2World& world);

    ~Box2DComponent();

    void update() override;

    b2Body* getBody();
};
