#include "Engine.h"
#include "ComponentsInclude.h"
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
    Engine::gameObjects.reserve(1000);
    
    b2Vec2 gravity(0.0f, 0.0f);
    m_world = new b2World(gravity);

    isRunning = true;
    return true;
};

// Handle events (static)

//TODO INPUT IS NOT COMPLETELY RIGHT
void Engine::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            Input::m_keysDown.insert(event.key.keysym.sym);
        }
        else if (event.type == SDL_KEYUP) {
            Input::m_keysDown.erase(event.key.keysym.sym);
        }
    }
    // Call static Input method
};

// Update all game objects (static)
void Engine::update() {
    auto body = player->getComponent<BodyComponent>()->getBody();
    camera.setCenter(body->GetPosition().x, body->GetPosition().y);
    handleInput();
    //auto p = player->get<BodyComponent>()->xPos;

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);

    //for (auto& gameObject : mapGameObjects) {
    //m_world.Step(timeStep, velocityIterations, positionIterations);
    //    gameObject.second->update();  // Update each GameObject
    //}
    for (auto& gameObject : gameObjects) {
        //m_world->Step(timeStep, velocityIterations, positionIterations);
        gameObject->update();  // Update each GameObject
    }
};

// Render all game objects (static)
void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //for (auto& gameObject : mapGameObjects) {
    //    gameObject.second->draw();  // Draw each GameObject
    //}
    for (auto& gameObject : gameObjects) {
        gameObject->draw();  // Draw each GameObject
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
    createWorld();
    loadPlayer();
    player = gameObjects.back().get();
    while (isRunning) {
        update();
        render();
        //SDL_Delay(16);
    }
    clean();
};
void Engine::loadPlayer() {
    const std::string jsonObjectsFile = "./assets/World.json";
    GameObjectLoader loadObjects(jsonObjectsFile);
}
void Engine::createWorld() {
    auto obj = std::make_unique<GameObject>();
    int startX = 100, startY = 100, rows = 1, cols = 1, tileWidth = 640, tileHeight = 640;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // Calculate tile position
            float tileX = startX + x * tileWidth;
            float tileY = startY + y * tileHeight;

            // Create a new game object for each tile
            auto floorTile = std::make_unique<GameObject>();

            // Add a BodyComponent for the floor tile
            floorTile->addComponent<BodyComponent>(tileX, tileY, tileWidth, tileHeight, 1);

            // Add a SpriteComponent to render the floor tile
            floorTile->addComponent<SpriteComponent>("floor_plain", "floor_plain");

            // Add the floor tile to the engine
            
            gameObjects.push_back(std::move(floorTile));
        }
    }

}

SDL_Renderer* Engine::getRenderer() {
    return renderer;
};

void Engine::spawnObject() {
    auto obj = std::make_unique<GameObject>();
    
    // Add components like BodyComponent and SpriteComponent
    obj->addComponent<BodyComponent>(60.0f, -100.0f, 100.0f, 100.0f, 0); // Example size: 1x1 meters
    obj->addComponent<SpriteComponent>("brick2", "spawnable");

    // Add the new game object to the engine
    gameObjects.push_back(std::move(obj));
    
    //mapGameObjects.insert({ "spawnable", std::move(obj) });
}
GameObject* Engine::player = nullptr;
float Engine::scale = 100.0f;
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
b2World* Engine::m_world=nullptr;

