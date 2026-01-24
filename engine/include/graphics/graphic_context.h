#ifndef GRAPHIC_CONTEXT
#define GRAPHIC_CONTEXT

#include <platform/window.h>

class GraphicContext {
    public:
        virtual void Init( int screen_x, int screen_y, int screen_w, int screen_h ); 
        virtual void RenderActive();
        virtual void Destroy();

        ~GraphicContext() {
            
        }
    private:

};

#endif