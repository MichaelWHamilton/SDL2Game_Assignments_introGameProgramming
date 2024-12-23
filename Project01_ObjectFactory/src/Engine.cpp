#include "Engine.h"
#include "ComponentsInclude.h"
#include "SDL2/SDL_mixer.h"
// Initialize the Engine (static)
bool Engine::init(const char* title, int width, int height) {
    //Engine::width = width;
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        return -1;
    }
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
};

// Update all game objects
void Engine::update() {
    auto body = player->getComponent<BodyComponent>()->getBody();
    camera.setCenter(body->GetPosition().x, body->GetPosition().y);
    handleInput();
    grabObjects();

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);

    for (auto& gameObject : gameObjects) {
        
        gameObject->update();  // Update each GameObject
    }
};

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

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
    Mix_FreeMusic(m_gameMusic);
    Mix_CloseAudio();
    SDL_Quit();
};
void Engine::grabObjects() {
    if (Input::isKeyDown(SDLK_e) && Engine::joint == nullptr) {
        auto body = player->getComponent<BodyComponent>()->getBody();
        b2Vec2 playerPos = body->GetPosition();
        float searchRadius = 25.0f; // Adjust the radius as needed

        b2AABB aabb;
        aabb.lowerBound = b2Vec2(playerPos.x - searchRadius, playerPos.y - searchRadius);
        aabb.upperBound = b2Vec2(playerPos.x + searchRadius, playerPos.y + searchRadius);

        // Create the query callback class
        class QueryCallback : public b2QueryCallback {
        private:
            b2Body* m_playerBody;
        public:
            QueryCallback(b2Body* playerBody) : m_playerBody(playerBody) {}
            bool ReportFixture(b2Fixture* fixture) override {
                // Check if the fixture's body is not the player's body and is a type of object you want to interact with
                if (fixture->GetBody() != m_playerBody) { // Make sure `body` is accessible here
                    // If the body is a dynamic box, perform any desired action
                    std::cout << "Found a body: " << fixture->GetBody()->GetType() << std::endl;

                    if (fixture->GetBody()->GetType() == b2_dynamicBody) {
                        b2RevoluteJointDef jointDef;
                        jointDef.bodyA = m_playerBody; // The player's body
                        jointDef.bodyB = fixture->GetBody(); // The found dynamic body
                        jointDef.localAnchorA.Set(110.0f, 0.0f); // Anchor point on the player's body
                        jointDef.localAnchorB.Set(0.0f, 0.0f); // Anchor point on the found body
                        jointDef.collideConnected = false; // Whether to allow collisions between bodies
                        jointDef.enableLimit = true;
                        

                        jointDef.enableMotor = false; 
                        
                        Engine::joint = Engine::m_world->CreateJoint(&jointDef);
                    }
                }
                return true; // Continue checking other fixtures
            }
        };

        // Create and run the query callback
        QueryCallback callback(body);
        Engine::m_world->QueryAABB(&callback, aabb);
    }

    if (Input::isKeyDown(SDLK_r)) {
        if (Engine::joint != nullptr) {
            Engine::m_world->DestroyJoint(Engine::joint); // Destroy the joint in the world
            Engine::joint = nullptr; // Reset the joint reference
        }
    }
}
// Check if the engine is still running (static)
bool Engine::running() {
    return isRunning;
};

// Add a GameObject to the engine (static)
void Engine::addGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));  // Add the game object to the list
};

void Engine::run() {
    createWorld();
    loadPlayer();
    loadMusic();
    player = gameObjects.back().get();
    while (isRunning) {
        update();
        render();
    }
    clean();
};
void Engine::loadPlayer() {
    const std::string jsonObjectsFile = "./assets/World.json";
    GameObjectLoader loadObjects(jsonObjectsFile);
}
void Engine::createWorld() {
    //int w = 1280;
    //int h = 720;

    //auto obj = std::make_unique<GameObject>();
    //auto obj = std::make_unique<GameObject>();
    //int startX = 200, startY = 200, rows = 3, cols = 3, tileWidth = 640, tileHeight = 640;
    //for (int y = 0; y < rows; ++y) {
    //    for (int x = 0; x < cols; ++x) {
    //        // Calculate tile position
    //        float tileX = startX + x * tileWidth;
    //        float tileY = startY + y * tileHeight;

    //        // Create a new game object for each tile
    //        auto floorTile = std::make_unique<GameObject>();

    //        // Add a BodyComponent for the floor tile
    //        floorTile->addComponent<BodyComponent>(tileX, tileY, tileWidth, tileHeight, 1);

    //        // Add a SpriteComponent to render the floor tile
    //        floorTile->addComponent<SpriteComponent>("floor_plain", "floor_plain");

    //        // Add the floor tile to the engine
    //        
    //        gameObjects.push_back(std::move(floorTile));
    //    }
    //}
    //createWall(screenWidth/2.0f, tileSize / 2.0f, screenWidth, tileSize);        // Top
    //createWall(halfWidth, SCREEN_HEIGHT - thickness / 2.0f, SCREEN_WIDTH, thickness); // Bottom
    //createWall(thickness / 2.0f, halfHeight, thickness, SCREEN_HEIGHT);      // Left
    //createWall(SCREEN_WIDTH - thickness / 2.0f, halfHeight, thickness, SCREEN_HEIGHT); // Right

    //float tileX = startX * tileWidth;
    //float tileY = startY * tileHeight;

    //// Create a new game object for each tile
    //auto floorTile = std::make_unique<GameObject>();

    //// Add a BodyComponent for the floor tile
    //floorTile->addComponent<BodyComponent>(0, 0, 1280, 32, 1);

    //// Add a SpriteComponent to render the floor tile
    //floorTile->addComponent<SpriteComponent>("wall1", "wall1");

    //// Add the floor tile to the engine
    //gameObjects.push_back(std::move(floorTile));

    // Define the dimensions of the room
    float roomWidth = 1280;   // Width of the room
    float roomHeight = 720;   // Height of the room
    float wallThickness = 32; // Thickness of each wall (adjust as needed)

    // Top wall
    float topWallX = 0;
    float topWallY = 0;
    auto topWall = std::make_unique<GameObject>();
    topWall->addComponent<BodyComponent>(topWallX, topWallY, roomWidth, wallThickness, 1);
    topWall->addComponent<SpriteComponent>("wall1", "wallTop1");
    gameObjects.push_back(std::move(topWall));

    // Bottom wall
    float bottomWallX = 0;
    float bottomWallY = roomHeight - wallThickness;
    auto bottomWall = std::make_unique<GameObject>();
    bottomWall->addComponent<BodyComponent>(bottomWallX, bottomWallY, roomWidth, wallThickness, 1);
    bottomWall->addComponent<SpriteComponent>("wall1", "wallBot1");
    gameObjects.push_back(std::move(bottomWall));

    // Top wall2
    
    auto topWall2 = std::make_unique<GameObject>();
    topWall2->addComponent<BodyComponent>(topWallX+roomWidth, topWallY, roomWidth, wallThickness, 1);
    topWall2->addComponent<SpriteComponent>("wall1", "wallTop2");
    gameObjects.push_back(std::move(topWall2));

    // Bottom wall2
    
    auto bottomWall2 = std::make_unique<GameObject>();
    bottomWall2->addComponent<BodyComponent>(bottomWallX+roomWidth, bottomWallY, roomWidth, wallThickness, 1);
    bottomWall2->addComponent<SpriteComponent>("wall1", "wallBot2");
    gameObjects.push_back(std::move(bottomWall2));

    // Top wall2
    
    auto topWall3 = std::make_unique<GameObject>();
    topWall3->addComponent<BodyComponent>(topWallX + roomWidth*2, topWallY, roomWidth, wallThickness, 1);
    topWall3->addComponent<SpriteComponent>("wall1", "wallTop3");
    gameObjects.push_back(std::move(topWall3));

    // Bottom wall2
    //float bottomWallX = 0;
    //float bottomWallY = roomHeight - wallThickness;
    auto bottomWall3 = std::make_unique<GameObject>();
    bottomWall3->addComponent<BodyComponent>(bottomWallX + roomWidth*2, bottomWallY, roomWidth, wallThickness, 1);
    bottomWall3->addComponent<SpriteComponent>("wall1", "wallBot3");
    gameObjects.push_back(std::move(bottomWall3));

    auto topWall4 = std::make_unique<GameObject>();
    topWall4->addComponent<BodyComponent>(topWallX + roomWidth * 3, topWallY, roomWidth, wallThickness, 1);
    topWall4->addComponent<SpriteComponent>("wall1", "wallTop3");
    gameObjects.push_back(std::move(topWall4));

    // Bottom wall2
    //float bottomWallX = 0;
    //float bottomWallY = roomHeight - wallThickness;
    auto bottomWall4 = std::make_unique<GameObject>();
    bottomWall4->addComponent<BodyComponent>(bottomWallX + roomWidth * 3, bottomWallY, roomWidth, wallThickness, 1);
    bottomWall4->addComponent<SpriteComponent>("wall1", "wallBot3");
    gameObjects.push_back(std::move(bottomWall4));

    // Left wall
    float leftWallX = -630;
    float leftWallY = 343;
    auto leftWall = std::make_unique<GameObject>();
    leftWall->addComponent<BodyComponent>(leftWallX, leftWallY, wallThickness, roomHeight, 1);
    leftWall->addComponent<SpriteComponent>("wall1", "wall3");
    gameObjects.push_back(std::move(leftWall));

    // Right wall
    float rightWallX = 630;
    float rightWallY = 343;
    auto rightWall = std::make_unique<GameObject>();
    rightWall->addComponent<BodyComponent>(rightWallX, rightWallY, wallThickness, roomHeight-200, 1);
    rightWall->addComponent<SpriteComponent>("wall1", "wall4");
    gameObjects.push_back(std::move(rightWall));

    // Right wall2
    //float rightWallX = 630;
    //float rightWallY = 343;
    auto rightWall2 = std::make_unique<GameObject>();
    rightWall2->addComponent<BodyComponent>(rightWallX+roomWidth, rightWallY, wallThickness, roomHeight - 200, 1);
    rightWall2->addComponent<SpriteComponent>("wall1", "wall4");
    gameObjects.push_back(std::move(rightWall2));
    // Right wall2
    auto rightWall3 = std::make_unique<GameObject>();
    rightWall3->addComponent<BodyComponent>(rightWallX + roomWidth + 140.0f, rightWallY, wallThickness, roomHeight - 200, 1);
    rightWall3->addComponent<SpriteComponent>("wall1", "wall4");
    gameObjects.push_back(std::move(rightWall3));

    auto rightWall4 = std::make_unique<GameObject>();
    rightWall4->addComponent<BodyComponent>(rightWallX + roomWidth*2, rightWallY, wallThickness, roomHeight - 200, 1);
    rightWall4->addComponent<SpriteComponent>("wall1", "wall4");
    gameObjects.push_back(std::move(rightWall4));

    auto rightWall5 = std::make_unique<GameObject>();
    rightWall5->addComponent<BodyComponent>(rightWallX + roomWidth * 2+140.0f, rightWallY, wallThickness, roomHeight - 200, 1);
    rightWall5->addComponent<SpriteComponent>("wall1", "wall4");
    gameObjects.push_back(std::move(rightWall5));

    //float boxW = 100;
    //float boxH = 100;
    //1st top box
    float boxTopX = 560; //560 620
    float boxTopY = 67;
    auto boxTop = std::make_unique<GameObject>();
    boxTop->addComponent<BodyComponent>(boxTopX, boxTopY, 100, 100, 0);
    boxTop->addComponent<SpriteComponent>("box", "box1");
    gameObjects.push_back(std::move(boxTop));
    //1st bot box
    float boxBotX = 560; //560 620
    float boxBotY = 620;
    auto boxBot = std::make_unique<GameObject>();
    boxBot->addComponent<BodyComponent>(boxBotX, boxBotY, 100, 100, 0);
    boxBot->addComponent<SpriteComponent>("box", "box2");
    gameObjects.push_back(std::move(boxBot));
    //2nd bot box
    float box3X = 2000; //560 620
    float box3Y = 620;
    auto box3 = std::make_unique<GameObject>();
    box3->addComponent<BodyComponent>(box3X, box3Y, 100, 100, 0);
    box3->addComponent<SpriteComponent>("box", "box3");
    gameObjects.push_back(std::move(box3));
    //2nd top box
    float box4X = 2000; //560 620
    float box4Y = 67;
    auto box4 = std::make_unique<GameObject>();
    box4->addComponent<BodyComponent>(box4X, box4Y, 100, 100, 0);
    box4->addComponent<SpriteComponent>("box", "box4");
    gameObjects.push_back(std::move(box4));

    boxTopX = 1850; //560 620
    boxTopY = 67;
    auto boxTop2 = std::make_unique<GameObject>();
    boxTop2->addComponent<BodyComponent>(boxTopX, boxTopY, 100, 100, 0);
    boxTop2->addComponent<SpriteComponent>("box", "box1");
    gameObjects.push_back(std::move(boxTop2));
    //1st bot box
    boxBotX = 1850; //560 620
    boxBotY = 620;
    auto boxBot2 = std::make_unique<GameObject>();
    boxBot2->addComponent<BodyComponent>(boxBotX, boxBotY, 50, 50, 0);
    boxBot2->addComponent<SpriteComponent>("box", "box2");
    gameObjects.push_back(std::move(boxBot2));


    //3rd set
    box3X = 3290; //560 620
    box3Y = 620;
    auto box33 = std::make_unique<GameObject>();
    box33->addComponent<BodyComponent>(box3X, box3Y, 100, 100, 0);
    box33->addComponent<SpriteComponent>("box", "box3");
    gameObjects.push_back(std::move(box33));
    //2nd top box
    box4X = 3290; //560 620
    box4Y = 67;
    auto box43 = std::make_unique<GameObject>();
    box43->addComponent<BodyComponent>(box4X, box4Y, 100, 100, 0);
    box43->addComponent<SpriteComponent>("box", "box4");
    gameObjects.push_back(std::move(box43));

    boxTopX = 3140; //560 620
    boxTopY = 67;
    auto boxTop23 = std::make_unique<GameObject>();
    boxTop23->addComponent<BodyComponent>(boxTopX, boxTopY, 100, 100, 0);
    boxTop23->addComponent<SpriteComponent>("box", "box1");
    gameObjects.push_back(std::move(boxTop23));
    //1st bot box
    boxBotX = 3140; //560 620
    boxBotY = 620;
    auto boxBot23 = std::make_unique<GameObject>();
    boxBot23->addComponent<BodyComponent>(boxBotX, boxBotY, 100, 100, 0);
    boxBot23->addComponent<SpriteComponent>("box", "box2");
    gameObjects.push_back(std::move(boxBot23));

    //enemy in zone 3
    boxBotX = 2900; //560 620
    boxBotY = 350;
    auto boxBotEnemy = std::make_unique<GameObject>();
    boxBotEnemy->addComponent<BodyComponent>(boxBotX, boxBotY, 100, 100, 0);
    boxBotEnemy->addComponent<SpriteComponent>("enemy", "enemy");
    gameObjects.push_back(std::move(boxBotEnemy));

}

void Engine::createWall(float x, float y, float width, float height) {

    auto obj = std::make_unique<GameObject>();

    obj->addComponent<BodyComponent>(x, y, width, height, 1);
    obj->addComponent<SpriteComponent>("floor_plain", "floor_plain");
    /*b2BodyDef wallDef;
    wallDef.position.Set(x, y);
    wallDef.type = b2_staticBody;
    b2Body* wallBody = Engine::m_world->CreateBody(&wallDef);
    b2PolygonShape wallShape;
    wallShape.SetAsBox(width / 2.0, height / 2.0f);
    wallBody->CreateFixture(&wallShape, 0.0f);*/
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

void Engine::loadMusic() {
    Mix_Music* m_gameMusic = Mix_LoadMUS(".\\assets\\sounds\\maingamemusic-6082.ogg");

    if (!m_gameMusic) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_FadeInMusic(m_gameMusic, -1, 5000);
    Mix_VolumeMusic(30);
}

GameObject* Engine::player = nullptr;
float Engine::scale = 100.0f;
bool Engine::isRunning = false;
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
std::vector<std::unique_ptr<GameObject>> Engine::gameObjects;
std::unordered_map<std::string, std::unique_ptr<GameObject>> Engine::mapGameObjects;
int Engine::screenWidth = 1280;
int Engine::screenHeight = 720;
int Engine::tileSize = 32;
std::vector<std::unique_ptr<GameObject>> Engine::toAdd;
std::vector<std::unique_ptr<GameObject>> Engine::toDelete;
Camera Engine::camera(0.0f, 0.0f, 1.0f, 0.0f);
b2World* Engine::m_world=nullptr;
b2Joint* Engine::joint = nullptr;
Mix_Music* Engine::m_gameMusic = nullptr;

