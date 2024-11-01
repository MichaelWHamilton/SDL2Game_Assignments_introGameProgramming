#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "Component.h"
class GameObject {
public:
    void addComponent(const std::string& name, std::unique_ptr<Component> component) {
        components[name] = std::move(component);
    }

    void update() {
        /*for (auto& [name, component] : components) {
            component->update();
        }*/
        for (auto& pair : components) {
            auto& component = pair.second;
            component->update();
        }
    }

    void draw() {
        /*for (auto& [name, component] : components) {
            component->draw();
        }*/
        for (auto& pair : components) {
            auto& component = pair.second;
            component->draw();
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Component>> components;
};