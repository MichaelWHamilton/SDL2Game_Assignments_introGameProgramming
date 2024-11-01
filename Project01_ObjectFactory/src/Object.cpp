#include "Object.h"
Object::Object() : name("placeholder"), x(0.0f), y(0.0f), angle(0.0f) {}
Object::Object(const std::string& name, float x, float y, float angle) : name(name), x(x), y(y), angle(angle) {}

std::string Object::getName() const { return name; }
float Object::getX() const { return x; }
float Object::getY() const { return y; }
float Object::getAngle() const { return angle; }

