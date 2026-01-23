#include <core/application.h>

bool Application::m_isRunning = true;
GraphicContext* Application::s_graphicCTX = nullptr;

void Application::Init( ) {
    xv::UserSettings settings = Bootstrap::GetUserSettings();

    bool bWindowInit = Window::Create( settings );
    if ( bWindowInit ) {
        XV_LOG_DEBUG("SDL {}: {}", "Window", "Window sucessfully initiated.");
    }

    if (settings.graphics.api == xv::GraphicsAPI::OpenGL) {
        s_graphicCTX = new GLContext();
    }

    if (s_graphicCTX == nullptr) {
        // TODO: Proper error handling here
        return;
    }

    s_graphicCTX->Init(0, 0, settings.graphics.ScreenW, settings.graphics.ScreenH); // TODO: Replace with actual window resoltion like Window::GetResoltion
}

void Application::BeginFrame() {
    Time::Update();

    if (!Window::PollActiveEvents()) {
        m_isRunning = false;
    }
}

void Application::RenderFrame() {
    XV_LOG_DEBUG("{} : {}", "Application", "Render Frame");
    s_graphicCTX->RenderActive();
}

void Application::UpdateFrame( float dt ) {
    //DEBUG XV_LOG_DEBUG("{} : {} {}", "Application", "Update : DELTA_TIME = ", dt);
}

void Application::EndFrame() {
    Input::Clear();
}

void Application::Close() {
   XV_LOG_DEBUG("{} : {}", "Application", "CLOSING");

   delete s_graphicCTX;
}