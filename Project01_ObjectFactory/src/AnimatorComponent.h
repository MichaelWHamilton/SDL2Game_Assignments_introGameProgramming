#pragma once
#pragma once
#include "Component.h"
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class AnimatorComponent : public Component {
public:
    AnimatorComponent(GameObject& parent, int frameRate = 10);

    // Add an animation sequence with a name and frames
    void addAnimation(const std::string& animationName, std::vector<SDL_Texture*> frames);

    // Set the current animation to play
    void setAnimation(const std::string& animationName);

    // Update frame based on the animation timing
    void update() override;

    // Draw the current frame of the active animation
    void draw() override;

private:
    struct Animation {
        std::vector<SDL_Texture*> frames;
        int frameCount;
    };

    std::unordered_map<std::string, Animation> animations;  // Stores animations by name
    std::string currentAnimation;
    int currentFrame = 0;
    int frameRate;            // Frames per second
    int frameCounter = 0;     // Counts updates for timing frame switches
};
