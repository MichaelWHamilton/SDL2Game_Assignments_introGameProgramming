//#include "Library.h"
//
//Library::Library()
//{
//	registerObject("Tree", Tree::create);
//	registerObject("Water", Water::create);
//	registerObject("Rock", Rock::create);
//	registerObject("Dog", Dog::create);
//
//	registerObjectJSON("Tree", Tree::createJSON);
//	registerObjectJSON("Water", Water::createJSON);
//	registerObjectJSON("Dog", Dog::createJSON);
//	registerObjectJSON("Rock", Rock::createJSON);
//
//	registerObjectYAML("Tree", Tree::createYAML);
//	registerObjectYAML("Water", Water::createYAML);
//	registerObjectYAML("Dog", Dog::createYAML);
//	registerObjectYAML("Rock", Rock::createYAML);
//
//}
//void Library::registerObject(const std::string& objectType, std::function<std::unique_ptr<Object>(const tinyxml2::XMLElement*)> creator)
//{
//	libraryXML[objectType] = creator;
//}
//
//std::unique_ptr<Object> Library::createObject(const std::string& objectType, const tinyxml2::XMLElement* xmlElement) const
//{
//	//std::cout << objectType;
//	if (libraryXML.empty())
//	{
//		//std::cout << "map is empty so can't find anything anyway, error lies here\n";
//	}
//	auto it = libraryXML.find(objectType);
//	if (it != libraryXML.end())
//	{
//		//std::cout << "found object\n";
//		return it->second(xmlElement);
//	}
//	else return nullptr;
//}
//
//std::unique_ptr<Object> Library::createObjectJSON(const std::string& objectType, const nlohmann::json_abi_v3_11_3::json* jsonElement) const
//{
//	//std::cout << objectType;
//	if (libraryJSON.empty())
//	{
//		//std::cout << "map is empty so can't find anything anyway, error lies here\n";
//	}
//	auto it = libraryJSON.find(objectType);
//	if (it != libraryJSON.end())
//	{
//		//std::cout << "found object\n";
//		return it->second(jsonElement);
//	}
//	else return nullptr;
//}
//void Library::registerObjectJSON(const std::string& objectType, std::function<std::unique_ptr<Object>(const nlohmann::json_abi_v3_11_3::json*)> creator)
//{
//	libraryJSON[objectType] = creator;
//}
//
//std::unique_ptr<Object> Library::createObjectYAML(const std::string& objectType, const YAML::Node* yamlElement) const
//{
//	//std::cout << objectType;
//	if (libraryYAML.empty())
//	{
//		//std::cout << "map is empty so can't find anything anyway, error lies here\n";
//	}
//	auto it = libraryYAML.find(objectType);
//	if (it != libraryYAML.end())
//	{
//		//std::cout << "found object\n";
//		return it->second(yamlElement);
//	}
//	else return nullptr;
//}
//void Library::registerObjectYAML(const std::string& objectType, std::function<std::unique_ptr<Object>(const YAML::Node*)> creator)
//{
//	libraryYAML[objectType] = creator;
//}
