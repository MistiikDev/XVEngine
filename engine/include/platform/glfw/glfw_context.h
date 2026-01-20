#ifndef GLFW_CONTEXT_H
#define GLFW_CONTEXT_H

#include <glad.h>
#include <GLFW/glfw3.h>
#include <core/log/log.h>
#include <core/config/user_config.h>

class GLFWContext {
    public: 
        GLFWContext() = delete;
        ~GLFWContext() = delete;

        static bool Init( const xv::UserSettings& settings );
        static bool PollEvents (  );
        static bool Stop( );

    private:
        static void m_glfw_error_callback( int error, const char* description ) {
            XV_LOG_ERROR("GLFW [{}] : {}", error, description);
        };

        static int m_screen_w;
        static int m_screen_h;

        static xv::GraphicsAPI m_graphics_api;

        // OpenGL
        static GLFWwindow* m_window;

        // DirectX
        // HWND handlewindow = ..
};

#endif