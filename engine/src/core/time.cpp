#include <core/timexv.h>
#include <iostream>

float Time::s_DeltaTime;
CLOCK::time_point Time::s_last_time;

void Time::Init() {
    s_last_time = CLOCK::now();
}

void Time::Update() {
    auto now = CLOCK::now();
    auto delta = now - s_last_time;

    s_DeltaTime = std::chrono::duration<float>(delta).count();
    s_last_time = now;
}


float Time::DeltaTime() {
    return s_DeltaTime;
}