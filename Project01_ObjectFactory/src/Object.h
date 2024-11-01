#pragma once
#include <iostream>
#include <memory>
#include <tinyxml2.h>
#include "yaml-cpp/yaml.h"
#include "nlohmann/json.hpp"

class Object {
public:
	Object();
	Object(const std::string& name, float x, float y, float angle);
	virtual ~Object() = default;
	virtual void update() = 0;
	virtual void draw() = 0;
	
	std::string getName() const;
	float getX() const;
	float getY() const;
	float getAngle() const;

	protected:
	std::string name;
	float x;
	float y;
	float angle;
};