#pragma once

class GameObject; // Forward declaration

class Component {
protected:
    GameObject& parent; // Reference to the parent GameObject
    //SDL_Renderer* renderer;
public:
    Component(GameObject& parent) : parent(parent) {}
    virtual ~Component() = default;

    // Method to get the parent GameObject
    GameObject& getParent() {
        return parent;
    }
    //SDL_Renderer* getRenderer() const { return renderer; }

    virtual void update() = 0; // Pure virtual function for updating
    virtual void draw() = 0;   // Pure virtual function for drawing
};
