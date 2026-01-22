#include <core/application.h>

bool Application::m_isRunning = true;

void Application::Init( ) {
    xv::UserSettings settings = Bootstrap::GetUserSettings();

    bool bWindowInit = Window::Create( settings );
    if ( bWindowInit ) {
        XV_LOG_DEBUG("SDL {}: {}", "Window", "Window sucessfully initiated.");
    }
}

void Application::BeginFrame() {
    Time::Update();

    if (!Window::PollActiveEvents()) {
        m_isRunning = false;
    }
}

void Application::RenderFrame() {

}

void Application::UpdateFrame( float dt ) {
    XV_LOG_DEBUG("{} : {} {}", "Application", "Update : DELTA_TIME = ", dt);
}

void Application::EndFrame() {
    
}

void Application::Close() {
   XV_LOG_DEBUG("{} : {}", "Application", "CLOSING");
}