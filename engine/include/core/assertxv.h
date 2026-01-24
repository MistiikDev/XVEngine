#ifndef RWXV_H
#define RWXV_H

#include <assert.h>
#include <core/log/log.h>

#define XV_ASSERT(...) ::xv::rw::ReadFile(__VA_ARGS__);

namespace xv {
    namespace assert {
        inline void Assert( bool condition ) {

        };

        inline void WriteFile( ) {

        };
    };
};

#endif // LOG_H
