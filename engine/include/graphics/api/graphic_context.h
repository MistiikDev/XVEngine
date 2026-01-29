#ifndef GRAPHIC_CONTEXT
#define GRAPHIC_CONTEXT

#include <platform/window.h>
#include <world/scene.h>

class GraphicContext {
    public:
        virtual void Init( int screen_x, int screen_y, int screen_w, int screen_h ); 
        virtual void PassBatch( Scene& scene );
        virtual void RenderActive( );
        virtual void Destroy();

        virtual void PrepareRender();
        virtual void SwapBuffers();

        ~GraphicContext() {
            
        }
        
    protected:
        static Scene* s_activeScene;

};

#endif