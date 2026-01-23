#ifndef WINDOW_H
#define WINDOW_H

#include <core/config/user_config.h>
#include <core/log/log.h>
#include <core/input.h>

class Window {
    public: 
        static bool Create( xv::UserSettings& user_settings );
        static bool PollActiveEvents();

        static void GetWindowResolution(int& w, int& h) { w = s_screen_w; h = s_screen_h; };
        static SDL_Window* GetSDLWindow() { return Window::s_window; };

    private:
        static int s_screen_x;
        static int s_screen_y;

        static int s_screen_w;
        static int s_screen_h;

        static SDL_Window* s_window;
        static SDL_Event s_windowActiveEvents;
};

#endif