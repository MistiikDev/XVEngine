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
    } else if(settings.graphics.api == xv::GraphicsAPI::DirectX11) {
        s_graphicCTX = new DX11Context();
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

    s_graphicCTX->PrepareRender(); // TODO: pass a batch of verticies maybe...
}

void Application::UpdateFrame( float dt ) {
    //DEBUG XV_LOG_DEBUG("{} : {} {}", "Application", "Update : DELTA_TIME = ", dt);
}

void Application::RenderFrame() {
    s_graphicCTX->RenderActive();
}

void Application::EndFrame() {
    Input::Clear();

    s_graphicCTX->SwapBuffers();
}

void Application::Close() {
   XV_LOG_DEBUG("{} : {}", "Application", "CLOSING");

   delete s_graphicCTX;
}