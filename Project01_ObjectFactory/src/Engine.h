#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "Object.h"
#include "Library.h"
#include <fstream>
#include "SDL2/SDL.h"
#include "GameObject.h"
#include "Input.h"
class Engine {
public:
	//Engine(const std::string& levelPath);
	~Engine() = default;
	void loadLevel(const std::string& levelPath);
	void loadFromJSON(const std::string& levelPath);
	void loadFromXML(const std::string& levelPath);
	void loadFromYAML(const std::string& levelPath);
	//static void update();
	//static void draw();
	//bool run();
	// 
	// 
	//const std::vector<std::unique_ptr<Object>>& getObjects() const;

	static bool init(const char* title, int widt, int height);
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

private:
	/*std::unique_ptr<Library> objectLibrary;
	std::vector<std::unique_ptr<Object>> objects;
	bool isRunning;	*/

	static bool isRunning;                               // Engine running state (static)
	static SDL_Window* window;                           // SDL window (static)
	static SDL_Renderer* renderer;                       // SDL renderer (static)
	static std::vector<std::unique_ptr<GameObject>> gameObjects;  // Track game objects

};