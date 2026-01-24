#ifndef GL_CONTEXT
#define GL_CONTEXT

#include <glad/glad.h> 
#include <graphics/graphic_context.h>

#include <graphics/opengl/buffers/GLArray.h>
#include <graphics/opengl/buffers/GLBuf.h>
#include <graphics/opengl/buffers/GLShader.h>

class GLContext : public GraphicContext {
    public:
        void Init( int screen_x, int screen_y, int screen_w, int screen_h ) override;
        void RenderActive( ) override;
        void Destroy() override;

        void PrepareRender() override;
        void SwapBuffers() override;
        
    private:
        SDL_GLContext m_sdlContext;
        GLShader* m_activeShader;

        GLArray* m_cubeVAO;
        GLBuf* m_cubeVBO;
        GLBuf* m_cubeIBO;

        glm::mat4 cube_transform;

};

#endif