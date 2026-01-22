#include <platform/window.h>

int Window::s_screen_h;
int Window::s_screen_w;

SDL_Window* Window::s_window;
SDL_Event Window::s_windowActiveEvents;

bool Window::Create( xv::UserSettings& user_settings ) {
    if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
        XV_LOG_ERROR("SDL {} : {}", "INIT", "Error while SDL INIT ");

        return false;
    };

    if (user_settings.graphics.api == xv::GraphicsAPI::OpenGL) {
        user_settings.graphics.windowFlag |= SDL_WINDOW_OPENGL;
    }

    s_screen_w = user_settings.graphics.ScreenW;
    s_screen_h = user_settings.graphics.ScreenH;

    s_window = SDL_CreateWindow( 
        "XVEngine", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        user_settings.graphics.ScreenW, user_settings.graphics.ScreenH,
        user_settings.graphics.windowFlag
    );

    return true;
}

bool Window::PollActiveEvents() {
    SDL_PollEvent(&Window::s_windowActiveEvents);

    switch (Window::s_windowActiveEvents.type) {
        // Input::Listen(event)
        
        case SDL_QUIT: {
            return false;
        }

        default: {
            //
        }
    }
    
    return true;
}