#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "ComponentsInclude.h"

class GameObjectLoader {
public:
	GameObjectLoader(const std::string& objectFilePath) {
        std::ifstream file(objectFilePath);
        nlohmann::json jsonData;
        file >> jsonData;
        
        for (const auto& obj : jsonData["Objects"]) {
            auto gameObject = std::make_unique<GameObject>();

            if (obj["components"].contains("SpriteComponent")) {
                name = obj["components"]["SpriteComponent"]["name"];
                int width = obj["components"]["SpriteComponent"]["width"];
                int height = obj["components"]["SpriteComponent"]["height"];
                gameObject->add<SpriteComponent>(name, width, height);
            }

            if (obj["components"].contains("BodyComponent")) {
                int x = obj["components"]["BodyComponent"]["x"];
                int y = obj["components"]["BodyComponent"]["y"];
                gameObject->add<BodyComponent>(x, y);
            }

            if (obj["components"].contains("CharacterControllerComponent")) {
                int speed = obj["components"]["CharacterControllerComponent"]["speed"];
                gameObject->add<CharacterControllerComponent>(speed);
            }

            if (obj["components"].contains("FollowComponent")) {
                std::string targetName = obj["components"]["FollowComponent"]["target"];
                int distance = obj["components"]["FollowComponent"]["distance"];
                GameObject* target = Engine::mapGameObjects[targetName].get();
                gameObject->add<FollowComponent>(target, distance);
            }

            if (obj["components"].contains("MoveUpAndDownComponent")) {
                int range = obj["components"]["MoveUpAndDownComponent"]["range"];
                float speed = obj["components"]["MoveUpAndDownComponent"]["speed"];
                gameObject->add<MoveUpAndDownComponent>(range, speed);
            }

            Engine::mapGameObjects.insert({ name, std::move(gameObject) });
            //Engine::addGameObject(std::move(gameObject));
        }
	}
private:
    std::string name;
    
};