#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL_image.h>
#include <box2d/box2d.h>
#include <unordered_map>

class GameObject;
class Camera;
class Engine {
public:
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

    static Camera camera;
    static SDL_Renderer* getRenderer();
    static std::unordered_map<std::string, std::unique_ptr<GameObject>> mapGameObjects;
    static int screenWidth;
    static int screenHeight;
    static b2World m_world;
    static constexpr float scale=30.0f;
private:
    static bool isRunning;                               
    static SDL_Window* window; 
    static SDL_Renderer* renderer;         
    static std::vector<std::unique_ptr<GameObject>> gameObjects;
    static std::vector<std::unique_ptr<GameObject>> toAdd;
    static std::vector<std::unique_ptr<GameObject>> toDelete;
    //static std::unordered_map<GameObject*, b2Body*> m_bodyMap;

};
