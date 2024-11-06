/*Michael Hamilton*/
#define SDL_MAIN_HANDLED
#include <iostream>
#include "Object.h"
#include "Library.h"
#include "Engine.h"
#include <memory>
#include <string>
#include <vector>
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "GameObject.h"
#include "Textures.h"
#include "CharacterControllerComponent.h"
#include "FollowComponent.h"
#include "AIComponent.h"
#include "MoveUpAndDownComponent.h"
int main(int argc, char* argv[]) {
    if (!Engine::init("SDL2 Game Engine", 800, 600))
    {
        return -1;
    }

    SDL_Renderer* renderer = Engine::getRenderer();
    const std::string jsonTextureFile = "./assets/Textures.json";
    Textures::loadTextures(jsonTextureFile, renderer);
    
    

    // Create and configure a new GameObject
    auto triangle = std::make_unique<GameObject>();
    triangle->add<SpriteComponent>("triangle");
    triangle->add<BodyComponent>(100,100);
    triangle->add<CharacterControllerComponent>(10);

    std::shared_ptr<GameObject> triangleShared = std::shared_ptr<GameObject>(triangle.get());


    auto square = std::make_unique<GameObject>();
    square->add<SpriteComponent>("square");
    square->add<BodyComponent>(30, 100);
    square->add<FollowComponent>(triangleShared, 50);
    //square->add<AIComponent>(20);

    auto circle = std::make_unique<GameObject>();
    circle->add<SpriteComponent>("circle",100,75);
    circle->add<BodyComponent>(500, 100);
    circle->add<MoveUpAndDownComponent>(10, .1);



    // Add GameObject to vector
    Engine::addGameObject(std::move(triangle));
    Engine::addGameObject(std::move(square));
    Engine::addGameObject(std::move(circle));
    //Engine::addGameObject(std::move(obj2));

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