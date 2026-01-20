#include <platform/glfw/glfw_context.h>
#include <iostream>

int GLFWContext::m_screen_w = 1280;
int GLFWContext::m_screen_h = 720;
xv::GraphicsAPI GLFWContext::m_graphics_api = xv::GraphicsAPI::OpenGL;
GLFWwindow* GLFWContext::m_window = nullptr;

bool GLFWContext::Init( const xv::UserSettings& user_settings ) {
    if (!glfwInit()) {
        XV_LOG_ERROR("GLFW [{}]: {}", "INIT", "Failed to create GLFW Context");
       
        return false;
    }

    glfwSetErrorCallback( GLFWContext::m_glfw_error_callback );

    m_graphics_api = user_settings.graphics.api;
    m_screen_w = user_settings.graphics.ScreenW;
    m_screen_h = user_settings.graphics.ScreenH;

    if ( m_graphics_api == xv::GraphicsAPI::OpenGL ) {
        m_window = glfwCreateWindow( m_screen_w, m_screen_h , "XVENGINE", NULL, NULL);

        if (!m_window) {
            XV_LOG_ERROR("GLFW {}: {}", "WINDOW CREATION", " Could not create window.");
            
            glfwDestroyWindow(m_window);
            glfwTerminate();

            return false;
        }

        XV_LOG_DEBUG("GLFW {}: {}", "WINDOW", " Window instantiated");

        glfwMakeContextCurrent(m_window); // Set active context as static window

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
            XV_LOG_ERROR("GLFW {}: {}", "OPENGL", " Could not retrieve OpenGL addresses.");
            
            glfwDestroyWindow(m_window);
            glfwTerminate();

            return false;

        }

        XV_LOG_DEBUG("GLFW {}: {}", "OpenGL", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        glViewport(0, 0, m_screen_w, m_screen_h);
        glEnable(GL_DEPTH_TEST);

        return true;

    } else if ( m_graphics_api == xv::GraphicsAPI::DirectX11 ) {
        // Get HWND....
    }

    return false;
}

bool GLFWContext::PollEvents(  ) {
    while ( !glfwWindowShouldClose( m_window ) ) {
        glfwPollEvents(  );
    }   

    return true;
}