#include <graphics/api/opengl/gl_context.h>

GLContext::GLContext() {
    
}

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
}   

void GLContext::PassBatch( Scene& scene ) {
    this->s_activeScene = &scene;

    for ( const Mesh* mesh : scene.meshes ) {
        if ( m_vertexArrays.find(mesh->ID) != m_vertexArrays.end() ) // already inside
            continue;

        GLArray* vertexArray = new GLArray();
        GLBuf* vertexBuffer = new GLBuf();
        GLBuf* indexBuffer = new GLBuf();

        vertexBuffer->Create(GL_ARRAY_BUFFER);
        indexBuffer->Create(GL_ELEMENT_ARRAY_BUFFER);

        vertexArray->Bind();
        vertexBuffer->Bind();
        indexBuffer->Bind();

        vertexBuffer->Upload( &mesh->verticies.front(), sizeof(Vertex) * mesh->verticies.size(), mesh->verticies.size(),  GL_STATIC_DRAW );
        indexBuffer->Upload( &mesh->indicies.front(), sizeof(uint32_t) * mesh->indicies.size(), mesh->indicies.size(), GL_STATIC_DRAW );

        vertexArray->LinkAttribute((*vertexBuffer), 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // position
        vertexArray->LinkAttribute((*vertexBuffer), 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color

        this->m_vertexArrays[mesh->ID] = vertexArray;
        this->m_vertexBuffers[mesh->ID] = vertexBuffer;
        this->m_indexBuffers[mesh->ID] = indexBuffer;
    }
}

void GLContext::PrepareRender() {
    glClearColor( 0.52f, 0.80f, 0.92f, 1.0f ); // Default Color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_activeShader->Activate();
}

void GLContext::RenderActive( ) {
    for (const Mesh* mesh : this->s_activeScene->meshes) {
        GLArray* mesh_vertexArray = this->m_vertexArrays[mesh->ID];
        GLBuf* mesh_indexBuffer = this->m_indexBuffers[mesh->ID];

        mesh_vertexArray->Bind();
        mesh_indexBuffer->Bind();

        m_activeShader->SetMatrix4f("u_MVP", mesh->transform);
        glDrawElements(GL_TRIANGLES, mesh_indexBuffer->elementCount, GL_UNSIGNED_INT, (void*)(0)); // this crahes
    }
}
void GLContext::SwapBuffers() {
    SDL_GL_SwapWindow( Window::GetSDLWindow() );
}

void GLContext::Destroy() {

    //
    for (auto kv : this->m_vertexArrays) {
        GLArray* array = kv.second;
        delete array;
    }

    for (auto kv : this->m_vertexBuffers) {
        GLBuf* buffer = kv.second;
        delete buffer;
    }

    for (auto kv : this->m_indexBuffers) {
        GLBuf* index_buffer = kv.second;
        delete index_buffer;
    }

    delete m_activeShader;
    m_activeShader = nullptr;
}
