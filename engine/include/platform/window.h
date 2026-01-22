#ifndef WINDOW_H
#define WINDOW_H

#include <core/config/user_config.h>
#include <core/log/log.h>

class Window {
    public: 
        static bool Create( xv::UserSettings& user_settings );
        static bool PollActiveEvents();

    private:
        static int s_screen_w;
        static int s_screen_h;

        static SDL_Window* s_window;
        static SDL_Event s_windowActiveEvents;
};

#endif