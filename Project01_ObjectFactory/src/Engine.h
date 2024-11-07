#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>  // For std::unique_ptr
#include "GameObject.h"
#include "SDL2/SDL_image.h"
#include <box2d/box2d.h>
#include "Input.h"

class Engine {
public:
    static int width;

    // Initialize the Engine (static)
    static bool init(const char* title, int width, int height);

    // Handle events (static)
    static void handleEvents();

    // Update all game objects (static)
    static void update();

    // Render all game objects (static)
    static void render();

    // Clean up SDL resources (static)
    static void clean();

    // Check if the engine is still running (static)
    static bool running();
    // Add a GameObject to the engine (static)
    static void addGameObject(std::unique_ptr<GameObject> gameObject);

    // Run the engine (static)
    static void run();

    static SDL_Renderer* getRenderer();
    static std::unordered_map<std::string, std::unique_ptr<GameObject>> mapGameObjects;
    //static b2World* world;
private:
    static bool isRunning;                               // Engine running state (static)
    static SDL_Window* window;                           // SDL window (static)
    static SDL_Renderer* renderer;                       // SDL renderer (static)
    static std::vector<std::unique_ptr<GameObject>> gameObjects;
    static std::vector<std::unique_ptr<GameObject>> toAdd;
    static std::vector<std::unique_ptr<GameObject>> toDelete;// Track game objects
    

};
