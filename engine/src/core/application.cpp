#include <core/application.h>

bool Application::m_isRunning = true;
GraphicContext* Application::s_graphicCTX = nullptr;
Scene Application::scene;

Vertex cubeVertices[] = {
    {{-0.5f,-0.5f,-0.5f},{1,0,0}},
    {{ 0.5f,-0.5f,-0.5f},{0,1,0}},
    {{ 0.5f, 0.5f,-0.5f},{0,0,1}},
    {{-0.5f, 0.5f,-0.5f},{1,1,0}},
    {{-0.5f,-0.5f, 0.5f},{1,0,1}},
    {{ 0.5f,-0.5f, 0.5f},{0,1,1}},
    {{ 0.5f, 0.5f, 0.5f},{1,1,1}},
    {{-0.5f, 0.5f, 0.5f},{0,0,0}},
};

uint32_t cubeIndices[] = {
    0,1,2, 2,3,0,
    4,5,6, 6,7,4,
    0,4,7, 7,3,0,
    1,5,6, 6,2,1,
    3,2,6, 6,7,3,
    0,1,5, 5,4,0
};

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

    XV_LOG_DEBUG("App Graphics {}: {}", "USING Render API", (settings.graphics.api == xv::GraphicsAPI::DirectX11) ? "DirectX11" : "OpenGL");

    // INIT SCENE / TEMPLATE FOR NOW
    scene = Scene {};

    Mesh* default_mesh = new Mesh {};
    default_mesh->ID = 1;
    default_mesh->verticies = std::vector<Vertex>(std::begin(cubeVertices), std::end(cubeVertices));
    default_mesh->indicies =  std::vector<uint32_t>(std::begin(cubeIndices), std::end(cubeIndices));
    
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), (float)(settings.graphics.ScreenW) / (float)(settings.graphics.ScreenH), 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 model = glm::mat4(1.0f);

    default_mesh->transform = perspective * view * model;
    scene.meshes.push_back( default_mesh );

    //

    s_graphicCTX->Init(0, 0, settings.graphics.ScreenW, settings.graphics.ScreenH); // TODO: Replace with actual window resoltion like Window::GetResoltion
    s_graphicCTX->PassBatch( scene );
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
}