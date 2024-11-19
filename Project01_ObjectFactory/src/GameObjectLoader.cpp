#include "GameObjectLoader.h"
#include "ComponentsInclude.h"
GameObjectLoader::GameObjectLoader(const std::string& objectFilePath) {
    std::ifstream file(objectFilePath);
    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto& obj : jsonData["Objects"]) {
        auto gameObject = std::make_unique<GameObject>();
        int width, height;
        std::string texture, name;
        if (obj["components"].contains("SpriteComponent")) {
            texture = obj["components"]["SpriteComponent"]["texture"];
            name = obj["components"]["SpriteComponent"]["name"];
            //width = obj["components"]["SpriteComponent"]["width"];
            //height = obj["components"]["SpriteComponent"]["height"];
            gameObject->addComponent<SpriteComponent>(texture, name);
        }

        if (obj["components"].contains("BodyComponent")) {
            int x = obj["components"]["BodyComponent"]["x"];
            int y = obj["components"]["BodyComponent"]["y"];
            width = obj["components"]["BodyComponent"]["width"];
            height = obj["components"]["BodyComponent"]["height"];
            gameObject->addComponent<BodyComponent>(x, y, width, height);
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

        if (obj["components"].contains("Box2DComponent")) {
            auto bodyType = obj["components"]["Box2DComponent"]["bodyType"];
            gameObject->addComponent<Box2DComponent>();
        }

        Engine::mapGameObjects.insert({ name, std::move(gameObject) });
        //Engine::addGameObject(std::move(gameObject));
    }
}
