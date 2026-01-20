#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <glad/glad.h> 
#include <core/config/user_config.h>
#include <core/log/log.h>

#include <platform/glfw/glfw_context.h>

struct Bootstrap {
    public:
        static bool Init( ) {
            // Create User Default Settings 
            xv::UserSettings settings; // Fetch from last save later?
            bool bWindowInit = GLFWContext::Init( settings );

            if ( bWindowInit ) {
                XV_LOG_DEBUG("GLFW {}: {}", "Context", "Context sucessfully initiated.");

                GLFWContext::PollEvents( );
            }

            return false;
        }

    private:
        Bootstrap() = delete;
        ~Bootstrap() = delete;
};

#endif