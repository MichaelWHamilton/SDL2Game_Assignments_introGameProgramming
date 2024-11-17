#pragma once
#include "Object.h"

class Tree : public Object {
public:
	Tree(float x, float y, float angle);
	virtual ~Tree() = default;

	void update() override;
	void draw() override;

	static std::unique_ptr<Object> create(const tinyxml2::XMLElement* element);
	static std::unique_ptr<Object> createJSON(const nlohmann::json_abi_v3_11_3::json* element);
	static std::unique_ptr<Object> createYAML(const YAML::Node* element);
};
