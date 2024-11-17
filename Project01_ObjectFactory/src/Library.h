//#pragma once
//#include <iostream>
//#include <memory>
//#include <string>
//#include <functional>
//#include <unordered_map>
//#include "Object.h"
//#include "Tree.h"
//#include "Water.h"
//#include "Rock.h"
//#include "Dog.h"
//
//class Library {
//public:
//	Library();
//	~Library() = default;
//	//xml
//	void registerObject(const std::string& objectType, std::function<std::unique_ptr<Object>(const tinyxml2::XMLElement*)> creator);
//	std::unique_ptr<Object> createObject(const std::string& objectType, const tinyxml2::XMLElement* element) const;
//	//json
//	std::unique_ptr<Object> createObjectJSON(const std::string& objectType, const nlohmann::json_abi_v3_11_3::json* jsonElement) const;
//	void registerObjectJSON(const std::string& objectType, std::function<std::unique_ptr<Object>(const nlohmann::json_abi_v3_11_3::json*)> creator);
//	//yaml
//	std::unique_ptr<Object> createObjectYAML(const std::string& objectType, const YAML::Node* yamlElement) const;
//	void registerObjectYAML(const std::string& objectType, std::function<std::unique_ptr<Object>(const YAML::Node*)> creator);
//private:
//	std::unordered_map<std::string, std::function<std::unique_ptr<Object>(const tinyxml2::XMLElement*)>> libraryXML;
//	std::unordered_map<std::string, std::function<std::unique_ptr<Object>(const nlohmann::json_abi_v3_11_3::json*)>> libraryJSON;
//	std::unordered_map<std::string, std::function<std::unique_ptr<Object>(const YAML::Node*)>> libraryYAML;
//};
