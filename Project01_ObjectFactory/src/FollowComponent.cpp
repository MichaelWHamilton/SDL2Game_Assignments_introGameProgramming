#include "FollowComponent.h"

FollowComponent::FollowComponent(GameObject& parentObj, GameObject* targetObj, double distance)
    : Component(parentObj), m_target(targetObj), m_followDistance(distance) {}

void FollowComponent::update() {
    if (m_target) {
        GameObject& parent = getParent();
        // get target's position
        double targetX = m_target->getComponent<BodyComponent>()->getX();
        double targetY = m_target->getComponent<BodyComponent>()->getY();

        double deltaX = targetX - parent.getComponent<BodyComponent>()->getX();
        double deltaY = targetY - parent.getComponent<BodyComponent>()->getY();
        double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Move toward the target if beyond follow distance
        if (distance > m_followDistance) {
            double angle = std::atan2(deltaY, deltaX);
            parent.getComponent<BodyComponent>()->getX() += std::cos(angle) * 5;
            parent.getComponent<BodyComponent>()->getY() += std::sin(angle) * 5;
        }
    }
}

void FollowComponent::draw() {

}


