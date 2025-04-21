//
// Created by sadik on 4/20/2025.
//

#pragma once
#include <raylib.h>

class NovaTimer {
private:
    float timer;
public:
    float duration;

    NovaTimer() = default;

    explicit NovaTimer(float duration): duration(duration), timer(duration){}


    void update();
    float elapsed();
    void reset();
    bool done();
};