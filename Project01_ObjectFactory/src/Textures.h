#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>

class Textures {
public:
    // Load a texture from a file and store it with the given key
    static void loadTextures(const std::string& jsonfile, SDL_Renderer* renderer) {

        std::ifstream file(jsonfile);
        nlohmann::json jsonData;
        file >> jsonData;

        for (const auto& textureData : jsonData["textures"]){
            std::string name = textureData["name"];
            std::string path = textureData["path"];

            SDL_Surface* tempSurface = IMG_Load(path.c_str());
            if (!tempSurface) {
                SDL_Log("Failed to load surface: %s", SDL_GetError());
                return;
            }

            // Convert the surface into a texture
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
            SDL_FreeSurface(tempSurface);

            if (!texture) {
                SDL_Log("Failed to create texture: %s", SDL_GetError());
                return;
            }
            textureMap[name] = std::unique_ptr<SDL_Texture, SDL_Deleter>(texture);
        }
    }

    // Get a texture by its name
    static SDL_Texture* get(const std::string& name) {
        auto it = textureMap.find(name);
        if (it != textureMap.end()) {
            return it->second.get();  // Return raw pointer to the texture
        }
        return nullptr;
    }

    // Remove a texture by its name
    static void remove(const std::string& name) {
        textureMap.erase(name);
    }

    // Clear all textures
    static void clear() {
        textureMap.clear();
    }

private:
    // Custom deleter for SDL_Texture to handle SDL_DestroyTexture automatically
    struct SDL_Deleter {
        void operator()(SDL_Texture* texture) const {
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
    };

    // Static map to store textures with custom names for keys and unique_ptrs for automatic cleanup
    static std::unordered_map<std::string, std::unique_ptr<SDL_Texture, SDL_Deleter>> textureMap;
};


