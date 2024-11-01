#include "Input.h"

// Update the input state based on SDL events (static method)
void Input::processEvent(const SDL_Event& event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        keysDown.insert(event.key.keysym.sym);
        break;

    case SDL_KEYUP:
        keysDown.erase(event.key.keysym.sym);
        break;

    case SDL_MOUSEBUTTONDOWN:
        mouseButtonsDown.insert(event.button.button);
        break;

    case SDL_MOUSEBUTTONUP:
        mouseButtonsDown.erase(event.button.button);
        break;

    case SDL_MOUSEMOTION:
        mousePosition = { event.motion.x, event.motion.y };
        break;
    }
};

// Check if a specific key is currently down (static method)
bool Input::isKeyDown(SDL_Keycode key) {
    return keysDown.find(key) != keysDown.end();
};

// Check if a specific mouse button is currently down (static method)
bool Input::isMouseButtonDown(Uint8 button) {
    return mouseButtonsDown.find(button) != mouseButtonsDown.end();
};

// Get the current mouse position (static method)
std::pair<int, int> Input::getMousePosition() {
    return mousePosition;
};

// Definition of static members
std::set<SDL_Keycode> Input::keysDown;
std::set<Uint8> Input::mouseButtonsDown;
std::pair<int, int> Input::mousePosition = { 0, 0 };
