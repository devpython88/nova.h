//
// Created by sadik on 4/20/2025.
//

#pragma once
#include <raylib.h>

class NovaTimer {
private:
    float timer;
    bool paused;
public:
    float duration;

    NovaTimer() = default;

    explicit NovaTimer(float duration): duration(duration), timer(duration), paused(false){}


    void update();
    float elapsed();
    void reset();
    bool done();

    inline void pause(){ paused = true; }
    inline void unpause(){ paused = false; }

};