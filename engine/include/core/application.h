#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/bootstrap.h>
#include <core/timexv.h>
#include <platform/window.h>

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

};

#endif