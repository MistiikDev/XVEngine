#ifndef TIMEXV_H
#define TIMEXV_H

#include <chrono>

using CLOCK = std::chrono::steady_clock;

class Time {
    public:
        static void Init();
        static void Update();
        static float DeltaTime();

    private:
        static CLOCK::time_point s_last_time;
        static float s_DeltaTime;

};

#endif