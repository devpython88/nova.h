//
// Created by sadik on 4/20/2025.
//

#pragma once
#include <raylib.h>
#include "nova.h"

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





// Stopwatch


// Time scales
class timescale_t {
    public:
    int value;

    timescale_t() = default;
    timescale_t(float val): value(val){}
};

class seconds_t : public timescale_t {
    public:
    
    seconds_t() = default;
    seconds_t(float secs): timescale_t(secs){}
};

class milliseconds_t : public timescale_t {
    public:
    
    milliseconds_t() = default;
    milliseconds_t(float secs): timescale_t(secs * 1000){}
};

class minutes_t : public timescale_t {
    public:
    
    minutes_t() = default;
    minutes_t(float secs): timescale_t(secs / 60){}
};

// Stopwatch



class NovaStopwatch {
    private:
    float timer;
    bool paused;

    public:

    NovaStopwatch(): timer(0.0f), paused(false){}

    void tick();
    
    template <typename T>
    T get(){
        return T(timer);
    }

    void pause();
    void unpause();
};





















// irl timer

typedef struct {
    float duration;
    std::chrono::steady_clock::time_point time;
} RealworldTimer;

class NovaRealworldTimer {
    private:
    std::map<std::string, RealworldTimer> timers;

    public:

    NovaRealworldTimer(): timers(){}

    void addTimer(std::string name, float durationInSeconds);
    bool finished(std::string name);
    void removeTimer(std::string name);
    void clearTimers();
};