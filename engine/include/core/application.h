#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
    public: 
        static void Init( );
        static void Close ( );
        
        static void BeginFrame( );
        static void UpdateFrame( float dt );
        static void RenderFrame( ); 
        static void EndFrame( );

        static bool bIsRunning( );
};

#endif