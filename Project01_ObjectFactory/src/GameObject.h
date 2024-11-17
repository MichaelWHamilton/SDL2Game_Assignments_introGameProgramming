#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>
#include <iostream>
#include "Component.h"

class GameObject {
public:
    template <typename T>
    int getID() {
        return std::hash<std::type_index>()(std::type_index(typeid(T)));
    }


    // Add a component to the GameObject.
    template <typename T, typename... Args>
    void addComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        m_components[getID<T>()] = std::make_unique<T>(*this, std::forward<Args>(args)...);
    }

    // Get a component by type as a raw pointer.
    template <typename T>
    T* getComponent() {
        auto it = m_components.find(getID<T>());
        if (it != m_components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    // Update all components.
    void update();

    // Draw all components.
    void draw();

private:
    std::unordered_map<int, std::unique_ptr<Component>> m_components;
};
