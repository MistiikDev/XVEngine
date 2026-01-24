#include <graphics/opengl/gl_context.h>

// ------------------------
// Debug Cube Geometry
// ------------------------

struct DebugVertex {
    float pos[3];
    float col[3];
};

DebugVertex cubeVertices[] = {
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

void GLContext::Init( int screen_x, int screen_y, int screen_w, int screen_h ) {
    SDL_GLContext ctx = SDL_GL_GetCurrentContext();

    if (!ctx) {
        XV_LOG_ERROR("{} : {} {} ", "SDL", "OpenGL", "SDL_OpenGL Context NONE EXISTENT");

        return; // TODO Proper handling
    }

    gladLoadGL(); // TODO : Check return error
    glViewport(screen_x, screen_y, screen_w, screen_h);
    glEnable( GL_DEPTH_TEST );

    m_activeShader = new GLShader( DEFAULT_VERTEX_SHADER, DEFAULT_FRAG_SHADER );

    if (m_activeShader == nullptr) {
        XV_LOG_ERROR("{} {} : {}", "OpenGL Shader", "MEMORY HEAP FAILURE", "Could not allocate shader memory.");
    }

    m_cubeVAO = new GLArray();
    m_cubeVBO = new GLBuf();
    m_cubeIBO = new GLBuf();

    m_cubeVBO->Create(GL_ARRAY_BUFFER);
    m_cubeIBO->Create(GL_ELEMENT_ARRAY_BUFFER);

    m_cubeVAO->Bind();
    m_cubeVBO->Bind();
    m_cubeVBO->Upload( cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW );

    m_cubeVAO->LinkAttribute((*m_cubeVBO), 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // position
    m_cubeVAO->LinkAttribute((*m_cubeVBO), 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color

    m_cubeIBO->Bind();
    m_cubeIBO->Upload( cubeIndices, sizeof(cubeIndices), GL_STATIC_DRAW );

    m_cubeVAO->Unbind();
    m_cubeVBO->Unbind();
    m_cubeIBO->Unbind();

    glm::vec3 objectPosition = glm::vec3(0.0f);
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), (float)(screen_w) / (float)(screen_h), 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 model = glm::mat4(1.0f);

    cube_transform = perspective * view * model;
}   

void GLContext::RenderActive() {
    glClearColor( 0.52f, 0.80f, 0.92f, 1.0f ); // Default Color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_activeShader->Activate();
    m_activeShader->SetMatrix4f("u_MVP", cube_transform);

    m_cubeVAO->Bind();
    m_cubeIBO->Bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(0));

    SDL_GL_SwapWindow( Window::GetSDLWindow() );

    m_cubeVAO->Unbind();
    m_cubeIBO->Unbind();
}

void GLContext::Destroy() {
    m_cubeVAO->Destroy();
    m_cubeVBO->Destroy();
    m_cubeIBO->Destroy();

    delete m_cubeVAO;
    delete m_cubeVBO;
    delete m_cubeIBO;

    delete m_activeShader;


    m_activeShader = nullptr;
}
