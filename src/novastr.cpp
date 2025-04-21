#include <string>
#include "novastr.h"

//
// Created by sadik on 4/20/2025.
//
std::string NovaTypeWriter::getCurrentText() const {
    return currentText;
}

void NovaTypeWriter::reset() {
    currentText = "";
    timer = timeBetweenCharacter;
}

void NovaTypeWriter::update() {
    if (paused) return;
    if (timer > 0.0f) {
        timer -= GetFrameTime();
        return;
    }
    timer = timeBetweenCharacter;

    if (index >= targetText.size()) return;

    currentText += targetText.at(index);
    index++;
}
