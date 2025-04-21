//
// Created by sadik on 4/20/2025.
//

#pragma once

#include <string>
#include <utility>
#include <raylib.h>

class NovaTypeWriter {
private:
    float timer;
    std::string currentText;
    int index;
    bool paused;

public:
    std::string targetText;
    float timeBetweenCharacter;

    NovaTypeWriter() = default;
    NovaTypeWriter(std::string targetText, float timeBetweenCharacter): targetText(std::move(targetText)), timeBetweenCharacter(timeBetweenCharacter),
        timer(timeBetweenCharacter), currentText(""), index(0), paused(false){}

    [[nodiscard]] std::string getCurrentText() const;
    void reset();
    void update();

    inline void pause(){ paused = true; }
    inline void unpause(){ paused = false; }
};