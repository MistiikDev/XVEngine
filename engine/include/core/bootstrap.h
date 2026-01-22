#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <core/config/user_config.h>
#include <core/log/log.h>

struct Bootstrap {
    public:
        static bool Init( ) {
            // Create User Default Settings 
            xv::UserSettings settings; // Fetch from last save later?
            s_settings = settings;

            return true;
        }

        static xv::UserSettings GetUserSettings() {
            return s_settings;
        }

    private:
        Bootstrap() = delete;
        ~Bootstrap() = delete;

        static xv::UserSettings s_settings;
};

#endif