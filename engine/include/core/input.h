#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <core/log/log.h>

class Input {
    public:
        static void Init();

        static bool IsKeyDown(SDL_KeyCode KEYCODE) { return s_keyboardInput[KEYCODE]; };
        static bool IsMouseButton1Down() { return bLMB; };
        static bool IsMouseButton2Down() { return bRMB; };

        static float GetMouseWheelDelta() { return lastWheelDelta; };

        static void Update( const SDL_Event& event );
        static void Clear();

    private:
        Input() = delete;
        ~Input() = delete;

        static std::unordered_map<SDL_Keycode, bool> s_keyboardInput;
        static bool bLMB, bRMB;

        static float lastWheelDelta;
};

#endif