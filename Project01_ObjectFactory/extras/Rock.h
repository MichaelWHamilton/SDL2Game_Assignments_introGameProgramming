#pragma once
#include "Object.h"
#include "nlohmann/json.hpp"
class Rock : public Object {
public:
	Rock(float x, float y, float angle);
	virtual ~Rock() = default;

	void update() override;
	void draw() override;

	static std::unique_ptr<Object> create(const tinyxml2::XMLElement* element);
	static std::unique_ptr<Object> createJSON(const nlohmann::json_abi_v3_11_3::json* element);
	static std::unique_ptr<Object> createYAML(const YAML::Node* element);
};
