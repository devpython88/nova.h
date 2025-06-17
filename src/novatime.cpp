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


// realword timer

void NovaRealworldTimer::addTimer(std::string name, float durationInSeconds)
{
    if (timers.find(name) == timers.end()){
        NovaLogger::info("Adding timer: " + name + "...");
        timers[name] = { durationInSeconds, std::chrono::steady_clock::now() };
    }
}

bool NovaRealworldTimer::finished(std::string name)
{
    // exit if aint found
    if (timers.find(name) == timers.end()) return false;

    // get now time and name time

    RealworldTimer timer = timers[name];

    auto beforeTime = timer.time;
    auto nowTime = std::chrono::steady_clock::now();

    std::chrono::duration<float> elapsed = nowTime - beforeTime;
    return elapsed.count() >= timer.duration;
}

void NovaRealworldTimer::removeTimer(std::string name)
{
    timers.erase(name);
}

void NovaRealworldTimer::clearTimers()
{
    timers.clear();
}
