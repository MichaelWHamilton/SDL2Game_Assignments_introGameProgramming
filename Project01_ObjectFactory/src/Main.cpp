/*Michael Hamilton*/
#define SDL_MAIN_HANDLED
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ComponentsInclude.h"


int main(int argc, char* argv[]) {
    if (!Engine::init("SDL2 Game Engine", 1280, 720))
    {
        return -1;
    }
    
    //TODO make main only contain Engine::run() perhaps?
    
    std::string s = "1";
    char z = '1';
    std::cout << s;
    SDL_Renderer* renderer = Engine::getRenderer();
    const std::string jsonTextureFile = "./assets/Textures.json";
    //const std::string jsonObjectsFile = "./assets/World.json";
    Textures::loadTextures(jsonTextureFile, renderer);
    //GameObjectLoader loadObjects(jsonObjectsFile);

    Engine::run();



    return 0;
}
