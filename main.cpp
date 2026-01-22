#include <iostream>
#include <core/application.h>

int main(int argc, char* argv[]) {
    // Startup Engine

    if ( Bootstrap::Init( ) ) {
        Application::Init( );

        while ( Application::bIsRunning() ) {
            Application::BeginFrame();
            Application::UpdateFrame( Time::DeltaTime() );

            Application::RenderFrame( );
            Application::EndFrame( );
        }

        Application::Close( );
    }

    return 0;
}

    