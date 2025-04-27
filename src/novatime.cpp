//
// Created by sadik on 4/20/2025.
//
#include "novatime.h"

void NovaTimer::update() {
    if (paused) return;
    if (timer > 0.0f){
        timer -= GetFrameTime();
    }
}

float NovaTimer::elapsed() {
    return duration - timer;
}

void NovaTimer::reset() {
    timer = duration;
}

bool NovaTimer::done() {
    return timer <= 0.0f;
}

void NovaStopwatch::tick()
{
    if (paused) return;

    timer += GetFrameTime();
}

void NovaStopwatch::pause()
{
    paused = true;
}

void NovaStopwatch::unpause()
{
    paused = false;
}
