#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/bootstrap.h>
#include <core/timexv.h>
#include <platform/window.h>
#include <graphics/api/opengl/gl_context.h>
#include <graphics/api/directx11/dx11_context.h>

// temporary
#include <graphics/objects/mesh.h>
#include <world/scene.h>

class Application {
    public: 
        static void Init( );
        static void Close ( );
        
        static void BeginFrame( );
        static void UpdateFrame( float dt );
        static void RenderFrame( ); 
        static void EndFrame( );

        static bool bIsRunning( ) { return m_isRunning; };
    private:
        Application() = delete;
        ~Application() = delete;

        static bool m_isRunning;
        static GraphicContext* s_graphicCTX;

        static Scene scene;

};

#endif