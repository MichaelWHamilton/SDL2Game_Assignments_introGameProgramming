/*Michael Hamilton*/
#define SDL_MAIN_HANDLED
#include <iostream>
#include "Object.h"
#include "Library.h"
#include "Engine.h"
#include <memory>
#include <string>
#include <vector>
#include "Textures.h"
#include "GameObjectLoader.h"
int main(int argc, char* argv[]) {
    if (!Engine::init("SDL2 Game Engine", 800, 600))
    {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();
    const std::string jsonTextureFile = "./assets/Textures.json";
    const std::string jsonObjectsFile = "./assets/ObjectsJSON.json";
    Textures::loadTextures(jsonTextureFile, renderer);
    GameObjectLoader loadObjects(jsonObjectsFile);

    Engine::run();

    return 0;
}












//int main()
//{
//	//switch path to load different file types
//	// 
//	// 
//	//going with one file type in project
//	//just wanted to learn how to pull from different file types
//	//and do a lil extra
//
//	std::string pathXML = "./assets/levelXML.xml";
//	std::string pathJSON = "./assets/levelJSON.json";
//	std::string pathYAML = "./assets/levelYAML.yaml";
//	std::unique_ptr<Engine> engine{ std::make_unique<Engine>(pathJSON) };
//
//	std::cout << "Engine Created!\n";
//	std::cout << "Testing:\n";
//	
//	for (const auto& objs : engine->getObjects())
//	{
//		std::cout << "Object: " << objs->getName() << "\nValues:\nX: " << objs->getX() << "\tY: " << objs->getY() << "\tAngle: " << objs->getAngle() << "\n";
//	}
//	return 0;
//}