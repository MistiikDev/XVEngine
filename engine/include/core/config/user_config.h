#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#pragma once

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

        GraphicsAPI api = GraphicsAPI::OpenGL;
    };

    struct UserSettings {
        GraphicSettings graphics;
        InputSettings inputs;
    };
};

#endif