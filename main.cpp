#include <iostream>
#include <core/bootstrap.h>
#include <core/application.h>

int main() {
    // Startup Engine

    if ( Bootstrap::Init( ) ) {
        Application::Init( );

        while ( Application::bIsRunning( ) ) {
            Application::BeginFrame();
            Application::UpdateFrame( 0.0F );

            Application::RenderFrame( );
            Application::EndFrame( );
        }

        Application::Close( );
    }
}