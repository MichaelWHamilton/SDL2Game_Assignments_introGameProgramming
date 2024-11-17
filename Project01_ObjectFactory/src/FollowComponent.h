#pragma once
#include "Component.h"
#include "GameObject.h"
#include <memory> 
#include <cmath>
#include "BodyComponent.h"

class FollowComponent : public Component {
private:
    GameObject* m_target;   
    double m_followDistance;              

public:
    FollowComponent(GameObject& parentObj, GameObject* targetObj, double distance);

    void update() override;

    void draw() override;
};


