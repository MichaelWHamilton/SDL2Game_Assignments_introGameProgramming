#pragma once
#include "Component.h"
#include <iostream>
#include <box2d/box2d.h>
#include <memory>

class GameObject;
class Box2DComponent : public Component {
private:
    b2Body* m_body;
    //b2World& m_world;
    enum Box2DBodyType{box2DDynamic, box2DStatic, box2DKinematic};
public:
    Box2DComponent(GameObject& parent);

    ~Box2DComponent();

    void update() override;
    void draw() override {};

    b2Body* getBody();
};
