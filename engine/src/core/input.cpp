#include <core/input.h>

std::unordered_map<SDL_Keycode, bool> Input::s_keyboardInput;
bool Input::bRMB;
bool Input::bLMB;

float Input::lastWheelDelta;

void Input::Init() {
    Input::lastWheelDelta = 0.0f;
    Input::bLMB = false;
    Input::bRMB = false;

    Input::s_keyboardInput.clear();
}

void Input::Update( const SDL_Event& event ) {
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            SDL_Keycode keycode = event.key.keysym.sym;
            Input::s_keyboardInput[keycode] = event.type == SDL_KEYDOWN;

            //DEBUG XV_LOG_DEBUG("{} : {} {}", "INPUT", (Input::s_keyboardInput[keycode] ? "PRESSED" : "RELEASED"), event.key.keysym.sym);

            break;
        };

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            bool pressed = (event.type == SDL_MOUSEBUTTONDOWN);

            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    bLMB = pressed;
                    break;

                case SDL_BUTTON_RIGHT:
                    bRMB = pressed;
                    break;
            }
        }
        
        case SDL_MOUSEWHEEL: {
            Input::lastWheelDelta = event.wheel.y;
            break;
        }
    }
}

void Input::Clear() {

    Input::lastWheelDelta = 0.0f;

}