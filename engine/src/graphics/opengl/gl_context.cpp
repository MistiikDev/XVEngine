#include <graphics/opengl/gl_context.h>

void GLContext::Init( int screen_x, int screen_y, int screen_w, int screen_h ) {
    SDL_GLContext ctx = SDL_GL_GetCurrentContext();

    if (!ctx) {
        XV_LOG_ERROR("{} : {} {} ", "SDL", "OpenGL", "SDL_OpenGL Context NONE EXISTENT");

        return; // TODO Proper handling
    }

    gladLoadGL(); // TODO : Check return error

    glViewport(screen_x, screen_y, screen_w, screen_h); // crash?
    glEnable( GL_DEPTH_TEST );
}

void GLContext::RenderActive() {
    glClearColor( 0.52f, 0.80f, 0.92f, 1.0f ); // Default Color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    SDL_GL_SwapWindow( Window::GetSDLWindow() );
}

void GLContext::Destroy() {

}
