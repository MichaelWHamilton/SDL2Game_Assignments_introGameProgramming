#pragma once
#include <box2d/box2d.h>
#include <iostream>

class CollisionListener : public b2ContactListener {
public:
    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override;

    // Called when two fixtures stop touching
    void EndContact(b2Contact* contact) override;
};
