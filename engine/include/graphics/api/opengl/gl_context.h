#ifndef GL_CONTEXT
#define GL_CONTEXT

#include <unordered_map>
#include <glad/glad.h> 
#include <graphics/api/graphic_context.h>

#include <graphics/api/opengl/buffers/GLArray.h>
#include <graphics/api/opengl/buffers/GLBuf.h>
#include <graphics/api/opengl/buffers/GLShader.h>

class GLContext : public GraphicContext {
    public:
        GLContext();
        
        void Init( int screen_x, int screen_y, int screen_w, int screen_h ) override;
        void PassBatch ( Scene& scene ) override;

        void RenderActive( ) override;
        void Destroy() override;

        void PrepareRender() override;
        void SwapBuffers() override;
        
    private:
        SDL_GLContext m_sdlContext;
        GLShader* m_activeShader;

        std::unordered_map<unsigned int, GLArray*> m_vertexArrays;
        std::unordered_map<unsigned int, GLBuf*> m_vertexBuffers;
        std::unordered_map<unsigned int, GLBuf*> m_indexBuffers;
};

#endif