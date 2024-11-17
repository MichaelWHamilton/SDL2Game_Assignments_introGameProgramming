#include "GameObjectLoader.h"


GameObjectLoader::GameObjectLoader(const std::string& objectFilePath) {
    std::ifstream file(objectFilePath);
    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto& obj : jsonData["Objects"]) {
        auto gameObject = std::make_unique<GameObject>();

        if (obj["components"].contains("SpriteComponent")) {
            m_name = obj["components"]["SpriteComponent"]["name"];
            int width = obj["components"]["SpriteComponent"]["width"];
            int height = obj["components"]["SpriteComponent"]["height"];
            gameObject->addComponent<SpriteComponent>(m_name, width, height);
        }

        if (obj["components"].contains("BodyComponent")) {
            int x = obj["components"]["BodyComponent"]["x"];
            int y = obj["components"]["BodyComponent"]["y"];
            gameObject->addComponent<BodyComponent>(x, y);
        }

        if (obj["components"].contains("CharacterControllerComponent")) {
            int speed = obj["components"]["CharacterControllerComponent"]["speed"];
            gameObject->addComponent<CharacterControllerComponent>(speed);
        }

        if (obj["components"].contains("FollowComponent")) {
            std::string targetName = obj["components"]["FollowComponent"]["target"];
            int distance = obj["components"]["FollowComponent"]["distance"];
            GameObject* target = Engine::mapGameObjects[targetName].get();
            gameObject->addComponent<FollowComponent>(target, distance);
        }

        if (obj["components"].contains("MoveUpAndDownComponent")) {
            int range = obj["components"]["MoveUpAndDownComponent"]["range"];
            float speed = obj["components"]["MoveUpAndDownComponent"]["speed"];
            gameObject->addComponent<MoveUpAndDownComponent>(range, speed);
        }

        Engine::mapGameObjects.insert({ m_name, std::move(gameObject) });
        //Engine::addGameObject(std::move(gameObject));
    }
}
