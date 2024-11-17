#include "GameObject.h"

// Update all components.
void GameObject::update() {
    for (auto& pair : m_components) {
        pair.second->update();
    }

}

// Draw all components.
void GameObject::draw() {
    for (auto& pair : m_components) {
        pair.second->draw();
    }
}

