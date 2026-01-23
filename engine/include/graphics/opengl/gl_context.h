#ifndef GL_CONTEXT
#define GL_CONTEXT

#include <glad/glad.h> 
#include <graphics/graphic_context.h>

#include <iostream>

class GLContext : public GraphicContext {
    public:
        void Init( int screen_x, int screen_y, int screen_w, int screen_h ) override;
        void RenderActive( ) override;
        void Destroy() override;
        
    private:
        SDL_GLContext m_sdlContext;

};

#endif