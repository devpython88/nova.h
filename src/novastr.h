//
// Created by sadik on 4/20/2025.
//

#pragma once

#include <string>
#include <utility>
#include <raylib.h>
#include <vector>
#include <sstream>

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



// Nova String


class NovaString : public std::string {
public:

    NovaString(): std::string(){}
    explicit NovaString(const char* str): std::string(str){}
    explicit NovaString(std::string str): std::string(str){}

    bool hasPrefix(std::string prefix);
    bool hasSuffix(std::string suffix);

    std::vector<NovaString> split(char delimiter);
    NovaString replace_(std::string __old, std::string __new);
};
