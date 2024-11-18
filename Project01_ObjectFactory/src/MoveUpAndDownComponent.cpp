#include "MoveUpAndDownComponent.h"
#include "ComponentsInclude.h"

MoveUpAndDownComponent::MoveUpAndDownComponent(GameObject& parentObj, double amplitude, double speed)
    : Component(parentObj), m_amplitude(amplitude), m_speed(speed), m_time(0.0) {}

void MoveUpAndDownComponent::update(){
    m_time += m_speed; // Increment time based on speed

    auto body = getParent().getComponent<BodyComponent>();
    body->getY() += m_amplitude * std::sin(m_time);
}

void MoveUpAndDownComponent::draw(){

}

