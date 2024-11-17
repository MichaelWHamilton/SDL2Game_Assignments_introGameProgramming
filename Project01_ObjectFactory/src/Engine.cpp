#include "Engine.h"

// Initialize the Engine (static)
bool Engine::init(const char* title, int width, int height) {
    //Engine::width = width;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    isRunning = true;
    return true;
};

// Handle events (static)
void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        Input::processEvent(event);  // Call static Input method
    }
};

// Update all game objects (static)
void Engine::update() {
    GameObject* player = Engine::mapGameObjects["triangle"].get();
    //auto p = player->get<BodyComponent>()->xPos;
    
    camera.setCenter(player->getComponent<BodyComponent>()->getX(), player->getComponent<BodyComponent>()->getY());

    for (auto& gameObject : mapGameObjects) {
        gameObject.second->update();  // Update each GameObject
    }
};

// Render all game objects (static)
void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (auto& gameObject : mapGameObjects) {
        gameObject.second->draw();  // Draw each GameObject
    }

    SDL_RenderPresent(renderer);
};

// Clean up SDL resources (static)
void Engine::clean() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
};

// Check if the engine is still running (static)
bool Engine::running() {
    return isRunning;
};

// Add a GameObject to the engine (static)
void Engine::addGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));  // Add the game object to the list
};

// Run the engine (static)
void Engine::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }

    clean();
};

SDL_Renderer* Engine::getRenderer() {
    return renderer;
};

bool Engine::isRunning = false;
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
std::vector<std::unique_ptr<GameObject>> Engine::gameObjects;
std::unordered_map<std::string, std::unique_ptr<GameObject>> Engine::mapGameObjects;
int Engine::screenWidth = 800;
int Engine::screenHeight = 600;
std::vector<std::unique_ptr<GameObject>> Engine::toAdd;
std::vector<std::unique_ptr<GameObject>> Engine::toDelete;
Camera Engine::camera(0.0f, 0.0f, 1.0f, 0.0f);

/*-----------------------------INTEGRATE THIS CODE LATER-------------------------*/

//
////Engine::Engine(const std::string& levelPath) :isRunning(true), objectLibrary(std::make_unique<Library>())
////{
////	loadLevel(levelPath);
////}
//
//void Engine::loadLevel(const std::string& levelPath)
//{
//	//tinyxml2::XMLDocument xmldoc;
//	//xmldoc.LoadFile(levelPath.c_str());
//	//tinyxml2::XMLElement* root = xmldoc.FirstChildElement("Level");	
//	//for (auto* object = root->FirstChildElement("Object"); object != nullptr; object = object->NextSiblingElement("Object")) {
//	//	std::string type = object->Attribute("type");
//	//	//std::unique_ptr<Object> obj = objectLibrary->createObject(type, object);
//	//	objects.push_back(objectLibrary->createObject(type, object));
//	//}
//
//	//loads based of what file is given/xml/json
//	if (levelPath.find(".xml") != std::string::npos)
//	{
//		loadFromXML(levelPath);
//	}
//	else if (levelPath.find(".json") != std::string::npos)
//	{
//		loadFromJSON(levelPath);
//	}
//	else if (levelPath.find(".yaml") != std::string::npos)
//	{
//		loadFromYAML(levelPath);
//	}
//	
//}
////const std::vector<std::unique_ptr<Object>>& Engine::getObjects() const { return objects; }
////void Engine::update() {};
////void Engine::draw() {};
////bool Engine::run()
////{
////	if (!isRunning) return false;
////	return isRunning;
////};
//
//void Engine::loadFromJSON(const std::string& levelPath)
//{
//	std::ifstream file(levelPath);
//	nlohmann::json data;
//	file >> data;
//
//	for (const auto& object : data["Objects"])
//	{
//		std::string type = object["type"].get<std::string>();
//		//objects.push_back(objectLibrary->createObjectJSON(type, &object));
//	}
//}
//	
//void Engine::loadFromXML(const std::string& levelPath)
//{
//	tinyxml2::XMLDocument xmldoc;
//	xmldoc.LoadFile(levelPath.c_str());
//	tinyxml2::XMLElement* root = xmldoc.FirstChildElement("Level");	
//	for (auto* object = root->FirstChildElement("Object"); object != nullptr; object = object->NextSiblingElement("Object"))
//	{
//		std::string type = object->Attribute("type");
//		//std::unique_ptr<Object> obj = objectLibrary->createObject(type, object);
//		//objects.push_back(objectLibrary->createObject(type, object));
//	}
//}
//
//void Engine::loadFromYAML(const std::string& levelPath)
//{
//	/*YAML::Node doc;
//	doc = YAML::LoadFile(levelPath);
//	
//	for (const auto& object : doc["Level"])
//	{
//		std::string type = object["type"].as<std::string>();
//		objects.push_back(objectLibrary->createObjectYAML(type, &object));
//	}*/
//	YAML::Node yamldoc = YAML::LoadFile(levelPath);
//
//	for (const auto& object : yamldoc["Body"]) 
//	{
//		std::string type = object["type"].as<std::string>();
//		//objects.push_back(objectLibrary->createObjectYAML(type, &object));
//	}
//}
//	




/* ---------------NEW CODE------------------- */






