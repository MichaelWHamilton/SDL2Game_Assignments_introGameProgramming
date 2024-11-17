#include "Input.h"

// Update the input state based on SDL events (static method)
void Input::processEvent(const SDL_Event& event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        m_keysDown.insert(event.key.keysym.sym);
        break;

    case SDL_KEYUP:
        m_keysDown.erase(event.key.keysym.sym);
        break;

    case SDL_MOUSEBUTTONDOWN:
        m_mouseButtonsDown.insert(event.button.button);
        break;

    case SDL_MOUSEBUTTONUP:
        m_mouseButtonsDown.erase(event.button.button);
        break;

    case SDL_MOUSEMOTION:
        m_mousePosition = { event.motion.x, event.motion.y };
        break;
    }
};

// Check if a specific key is currently down (static method)
bool Input::isKeyDown(SDL_Keycode key) {
    return m_keysDown.find(key) != m_keysDown.end();
};

// Check if a specific mouse button is currently down (static method)
bool Input::isMouseButtonDown(Uint8 button) {
    return m_mouseButtonsDown.find(button) != m_mouseButtonsDown.end();
};

// Get the current mouse position (static method)
std::pair<int, int> Input::getMousePosition() {
    return m_mousePosition;
};

// Definition of static members
std::set<SDL_Keycode> Input::m_keysDown;
std::set<Uint8> Input::m_mouseButtonsDown;
std::pair<int, int> Input::m_mousePosition = { 0, 0 };
