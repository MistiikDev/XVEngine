#ifndef RWXV_H
#define RWXV_H

#include <string>
#include <fstream>
#include <sstream>

#include <core/log/log.h>

#define XV_READ_FILE(...) ::xv::rw::ReadFile(__VA_ARGS__);
#define XV_WRITE_FILE(...) ::xv::rw::WriteFile(__VA_ARGS__);

namespace xv {
    namespace rw {
        inline std::string ReadFile( const char* fileLocation ) {
            std::ifstream file( fileLocation);

            if (!file) {
                XV_LOG_ERROR("{} : {} {} ", "READ-WRITE ERROR", "SHADER_ERR ", "Failed to open shader file.");

                return std::string();
            }

            std::stringstream buffer;
            buffer << file.rdbuf(); 

            return buffer.str();
        };

        inline void WriteFile( ) {

        };
    };
};

#endif // LOG_H
