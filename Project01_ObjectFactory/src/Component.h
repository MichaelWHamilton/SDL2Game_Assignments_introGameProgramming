#pragma once

class GameObject;

class Component {
private:
    GameObject& m_parent; //TODO
public:
    Component(GameObject& parent) : m_parent(parent) {}
    virtual ~Component() = default;

    //get parent GameObject
    GameObject& getParent() {
        return m_parent;
    }
    
    virtual void update() = 0; 
    virtual void draw() = 0;   
};
