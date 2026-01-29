#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#pragma once

#include <sdl2/SDL.h>

namespace xv {
    enum class GraphicsAPI {
        OpenGL,
        DirectX11
    };

    struct InputSettings {
        float MouseSensitivityX = 1.0f;
        float MouseSensitivityY = 1.0f;
    };

    struct GraphicSettings {
        int ScreenW = 1280;
        int ScreenH = 720;
        Uint32 windowFlag = SDL_WINDOW_ALLOW_HIGHDPI;
        
        GraphicsAPI api = GraphicsAPI::OpenGL;
    };

    struct UserSettings {
        GraphicSettings graphics;
        InputSettings inputs;
    };
};

#endif