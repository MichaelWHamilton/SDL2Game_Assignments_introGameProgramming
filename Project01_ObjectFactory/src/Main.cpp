/*Michael Hamilton*/
#define SDL_MAIN_HANDLED
#include <iostream>
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
