#pragma once
#include "Component.h"
#include "GameObject.h"
#include <memory> // For std::weak_ptr
#include <cmath>
#include "BodyComponent.h"


class FollowComponent : public Component {
private:
    GameObject* target;   // Weak pointer to the GameObject this component follows
    double followDistance;              

public:
    FollowComponent(GameObject& parentObj, GameObject* targetObj, double distance)
        : Component(parentObj), target(targetObj), followDistance(distance) {}

    void update() override {
        // Attempt to lock the weak pointer
        if (target) {
            GameObject& parent = getParent();
            // Access the target's BodyComponent position
            double targetX = target->get<BodyComponent>()->x();
            double targetY = target->get<BodyComponent>()->y();

            double deltaX = targetX - parent.get<BodyComponent>()->x();
            double deltaY = targetY - parent.get<BodyComponent>()->y();
            double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

            // Move toward the target if beyond follow distance
            if (distance > followDistance) {
                double angle = std::atan2(deltaY, deltaX);
                parent.get<BodyComponent>()->x() += std::cos(angle)*5;
                parent.get<BodyComponent>()->y() += std::sin(angle)*5;
            }
        }
    }

    void draw() override {
        
    }
};


