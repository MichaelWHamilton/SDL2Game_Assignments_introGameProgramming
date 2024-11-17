#include "Rock.h"

Rock::Rock(float x, float y, float angle) :Object("Rock", x, y, angle)
{
}
void Rock::update() {}
void Rock::draw() {}
std::unique_ptr<Object> Rock::create(const tinyxml2::XMLElement* element)
{
	float x = 0.0f, y = 0.0f, angle = 0.0f;
	const tinyxml2::XMLElement* body = element->FirstChildElement("Body");
	x = body->FloatAttribute("x", 0.0f);
	y = body->FloatAttribute("y", 0.0f);
	angle = body->FloatAttribute("angle", 0.0f);
	return std::make_unique<Rock>(x, y, angle);
}

std::unique_ptr<Object> Rock::createJSON(const nlohmann::json_abi_v3_11_3::json* element)
{
	float x = 0.0f, y = 0.0f, angle = 0.0f;
	x = (*element)["Body"]["x"];
	y = (*element)["Body"]["x"];
	angle = (*element)["Body"]["x"];
	return std::make_unique<Rock>(x, y, angle);
}

std::unique_ptr<Object> Rock::createYAML(const YAML::Node* element)
{
	float x = 0.0f, y = 0.0f, angle = 0.0f;
	x = (*element)["x"].as<float>();
	y = (*element)["y"].as<float>();
	angle = (*element)["angle"].as<float>();
	return std::make_unique<Rock>(x, y, angle);
}

