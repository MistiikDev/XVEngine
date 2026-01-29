#ifndef LOG_H
#define LOG_H

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#define XV_LOG_ERROR(...) ::xv::log::Error(__FILE__, __LINE__, __VA_ARGS__)
#define XV_LOG_DEBUG(...) ::xv::log::Debug(__FILE__, __LINE__, __VA_ARGS__)

namespace xv {
    namespace log {

        template <typename ...Args>
        inline void Error( const char* file, int line, const char* format, Args&& ...args ) {
            auto message = fmt::format(format, std::forward<Args>(args)...);

            fmt::print(stderr, "[ERROR] [{}:{}] {}\n", file, line, message);
        }

        template <typename ...Args>
        inline void Debug( const char* file, int line, const char* format, Args&& ...args ) {
            auto message = fmt::format(format, std::forward<Args>(args)...);

            fmt::print("[DEBUG] {} [{}:{}]\n", message, file, line);
        } 
    };
};

#endif // LOG_H
